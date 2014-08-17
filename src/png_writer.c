#include "png_writer.h"

/*
 * This function writes a png image to file, as with its reader counterpart will return true on 
 * success, false on failure
 */
bool write_png_to_file(PNGImage* img, char* filename)
{
    // First let's check to see if we have been given something we can write
    // Eventually I probably come up with a better validity check than simply 
    // all fields being non zero, but it should suffice for now
    if(!is_img_writeable(img))
    {
        fprintf(stderr, "[png_writer]: ERROR: Empty PNGImage struct given - there is nothing to write!\n");
        return false;
    }

    // Now let's see if we are able to open this file for writing
    FILE* png_f = fopen(filename, "wb");

    if(png_f)
    {
        fprintf(stderr, "[png_writer]: ERROR: Unable to open file %s for writing\n", filename);
        return false;
    }

    // Time to initialise some things 
    img->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if(!img->png_ptr)
    {
        fprintf(stderr, "[png_writer]: ERROR: Unable to create write struct\n");
        fclose(png_f);
        return false;
    }

    img->info_ptr = png_create_info_struct(img->png_ptr);

    if(!img->info_ptr)
    {
        fprintf(stderr, "[png_writer]: ERROR: Unable to create info struct\n");
        fclose(png_f);
        return false;
    }

    // If the next step goes wrong tell libpng what code we want it to run
    if(setjmp(png_jmpbuf(img->png_ptr)))
    {
        fprintf(stderr, "[png_writer]: ERROR: Problems while initialising IO\n");
        fclose(png_f);
        return false;
    }

    png_init_io(img->png_ptr, png_f);

    // Time to start writing stuff to file, starting with the PNG header
    if (setjmp(png_jmpbuf(img->png_ptr)))
    {
        fprintf(stderr, "[png_writer]: ERROR: Unable to write header for %s\n", filename);
        fclose(png_f);
        return false;
    }

    png_set_IHDR(img->png_ptr, img->info_ptr, img->width, img->height, 
                    img->bit_depth, img->color_type, PNG_INTERLACE_NONE,
                    PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(img->png_ptr, img->info_ptr);

    // Time to write the actual image
    if(setjmp(png_jmpbuf(img->png_ptr)))
    {
        fprintf(stderr, "[png_writer]: ERROR: Unable to write image to %s\n", filename);
        fclose(png_f);
        return false;
    }

    png_write_image(img->png_ptr, img->row_pointers);

    // Finish up
    if(setjmp(png_jmpbuf(img->png_ptr)))
    {
        fprintf(stderr, "[png_writer]: ERROR: Problem while finishing up\n");
        fclose(png_f);
        return false;
    }

    png_write_end(img->png_ptr, NULL);

    fclose(png_f);
    return true;
}
