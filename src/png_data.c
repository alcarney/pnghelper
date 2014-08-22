#include "png_data.h"

/*
 * This function initialises the PNGImage struct for us in future it may be
 * a good idea to make use of stdarg.h and add a ... argument that allow us
 * to specify optional arguments such as image height and width etc.
 */
bool new_png_image(PNGImage* img, IMGParams* params)
{
    // Check to see if we have been given any parameters if so use those
    // otherwise just create a blank image
    if (params != NULL)
    {
        img->width = params->width;
        img->height = params->height;
        img->color_type = params->color_type;
        img->bit_depth = 8; // We will only be able to create 8bit images for now

        int num_channels = 0;

        // Choose the number of channels the image will require
        switch(img->color_type)
        {
            // This only has one channel 
            case PNG_COLOR_TYPE_GRAY:
                num_channels = 1;       
                break;

            // Three channels
            case PNG_COLOR_TYPE_RGB:
                num_channels = 3;
                break;

            // Four channels
            case PNG_COLOR_TYPE_RGB_ALPHA:
                num_channels = 4;
                break;

            default:
                fprintf(stderr, "[new_image]: ERROR: Invalid colour type or color type unsupported\n");
                return false;
        }

        // Now allocate the memory
        img->row_pointers = (png_bytep*) malloc(img->height * sizeof(png_bytep));

        if(!img->row_pointers)
        {
            fprintf(stderr, "[new_image]: ERROR: Unable to allocate memory for the image\n");
            return false;
        }

        unsigned int i = 0;
        unsigned int j = 0;
        for(i = 0; i < img->width ; i++)
        {
            img->row_pointers[i] = (png_byte*) malloc((img->width * num_channels) * sizeof(png_byte));

            if(!img->row_pointers[i])
            {
                fprintf(stderr, "[new_image]: ERROR: Unable to allocate memory for the image\n");

                for(j = 0; j < i; j++)
                {
                    free(img->row_pointers[i]);
                    img->row_pointers[i] = NULL;
                }

                return false;
            }
        }
    }
    else   
    {
        // I think we can just initialise everything to zero
        img->width = 0;
        img->height = 0;
        img->color_type = 0;
        img->bit_depth = 0;
        img->row_pointers = NULL;
    }
    
    img->number_of_passes = 0;

    // It's good practice to initialise pointers to NULL
    img->png_ptr = NULL;
    img->info_ptr = NULL;

    return true;
    
}

/*
 * This function is for clearing up after an image struct has been finished with
 * de allocating all the memory and restoring it to its inital state ready for reuse 
 * or just as the program is closing
 */
void destroy_png_image(PNGImage* img)
{
    unsigned int i = 0;

    for (i =0 ; i< img->height; i++)
    {
        free(img->row_pointers[i]);
        img->row_pointers[i] = NULL;
    }

    free(img->row_pointers);
    img->row_pointers = NULL;

    img->width = 0;
    img->height = 0;
    img->color_type = 0;
    img->bit_depth = 0;
    img->number_of_passes = 0;

    img->png_ptr = NULL;
    img->info_ptr = NULL;

}

/*
 * Checks an image to see if it is in fact empty
 */
bool is_empty_img_struct(PNGImage* img)
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
 * Checks to see if an image is writable
 */
bool is_img_writeable(PNGImage* img)
{
    // Baiscally check every field, if it isn't NULL 
    // for pointers or 0 for the numeric fields then return false
    if (img->row_pointers == NULL)
        return false;

    if (img->height == 0 || img->width == 0 || img->bit_depth == 0 || img->color_type == 0)
        return false;

    // If we get this far then indeed we have an empty image struct so return true
    return true;
}
