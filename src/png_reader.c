#include "png_reader.h"

// Static function prototypes
static bool is_empty_img_struct(PNGImage* img);

/*
 * Checks an image to see if it is in fact empty
 */
static bool is_empty_img_struct(PNGImage* img)
{
    // Baiscally check every field, if it isn't NULL 
    // for pointers or 0 for the numeric fields then return false
    if (img->png_ptr != NULL || img->info_ptr != NULL || img->row_pointers != NULL)
        return false;

    if (img->height != 0 || img->width != 0 || img->bit_depth != 0 || img->color_type != 0)
        return false;

    // If we get this far then indeed we have an empty image struct so return true
    return true;
}

/*
 * This function reads in a png image from the filename given
 * returns true on success or false on fail
 */
bool read_png_from_file(PNGImage* img, char* filename)
{

    // Make sure we have been given an empty PNGImage struct
    if(!is_empty_img_struct(img))
    {
        fprintf(stderr, "[png_reader]: ERROR: You are attempting to load an image into "
                "an already populated PNGImgae struct, aborting...\n");
        return false;
    }

    // First things first lets see if we can open the file
    FILE* png_f = fopen(filename, "wb");

    if(!png_f)
    {
        fprintf(stderr, "[png_reader]: ERROR: Unable to open file %s\n", filename);
        return false;
    }

    // Next we need to verify that the file given is in fact a png file, 
    // this is done by checking the first 8 bytes of the file and see if they
    // match the signature as specified in the PNG specification. Luckily there
    // is a function that will do this for us
    
    // Let's read those first 8 bytes then
    char header[8];
    fread(header, 1, 8, png_f);

    // Now lets call that handy function then
    if(png_sig_cmp(header, 0, 8))
    {
        fprintf(stderr, "[png_reader]: ERROR: File %s is not a valid png imgae\n", filename);
        fclose(png_f);
        return false;
    }

    // Now we know we have a valid image to read let's initialise all the libpng bits
    img->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if(!img->png_ptr)
    {
        fprintf(stderr, "[png_reader]: ERROR: Unable to create read struct\n");
        fclose(png_f);
        return false;
    }

    img->info_ptr = png_create_info_struct(img->png_ptr);

    if(!img->info_ptr)
    {
        fprintf(stderr, "[png_reader]: ERROR: Unable to create info struct\n");
        fclose(png_f);
        return false;
    }

    // Tell libpng what we'd like it to run if it encounters an error during the next step
    if(setjmp(png_jmpbuf(info->png_ptr)))
    {
        fprintf(stderr, "[png_reader]: ERROR: Problems while initialising IO\n");
        fclose(png_f);
        return false;
    }

    // Time to let libpng set things up on its end
    png_init_io(img->png_ptr, png_f);

    // Tell libpng how many bytes we read in while checking the header
    png_set_sig_bytes(info_png_ptr, 8);

    // Next we need to get some info about the image we are going to read in
    png_read_info(img->png_ptr, img->info_ptr);

    img->width = png_get_image_width(img->png_ptr, img->info_ptr);
    img->height = png_get_image_height(img->png_ptr, img->info_ptr);
    img->color_type = png_get_color_type(img->png_ptr, img->info_ptr);
    img->bit_depth = png_get_bit_depth(img->png_ptr, img->info_ptr);

    // Also good to get information about interlacing at this point
    img->number_of_passes = png_set_interlace_handling(img->png_ptr);

    // I need to find out what this does
    png_read_update_info(img->png_ptr, img->info_ptr);

    // Last bit of housekeeping before we read the image into memory, we need
    // to tell libpng what we'd like to run on our end in case of an error
    if(setjmp(png_jmpbuf(info->png_ptr)))
    {
        fprintf(stderr, "[png_reader]: ERROR: Unable to read file %s\n", filename);
        fclose(png_f);

        // Don't forget if this code is running we will have got to the point where we
        // will have allocated the memory for the image which now needs to be freed
        unsigned int i = 0;

        for (i = 0; i < img->height ; i++)
        {
            free(img->row_pointers[i]);
            img->row_pointers = NULL;
        }

        free(img->row_pointers);
        img->row_pointers = NULL;

        return false;
    }

    // Allocate enough memory to store the image
    img->row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * img->height);

    if (!img->row_pointers)
    {
        fprintf(stderr, "[png_reader]: ERROR: Unable to allocate memory for image file %s\n", filename);
        fclose(png_f);
        return false;
    }

    unsigned int row = 0;

    for(row = 0; row < img->height : row++)
    {
        img->row_pointers[row] = (png_byte*) malloc(png_get_rowbytes(img->png_ptr, img->info_ptr));

        if(!img->row_pointers[row])
        {
            fprintf(stderr, "[png_reader]: ERROR: Unable to allocate memory for image file %s\n", filename);
            fclose(png_f);

            // We also need to deallocate any memory we may already have allocated
            unsigned int j = 0;

            for(j = 0; j < row; j++)
            {
                free(img->row_pointers[j]);
                img->row_pointers[j] = NULL;
            }

            // And the array of rows
            free(img->row_pointers);
            img->row_pointers = NULL;

            return false;
        }
    }

    // Now with the memory allocated let's finally read in this image
    png_read_image(img->png_ptr, img->row_pointers);

    fclose(png_f);
    return true;

}
