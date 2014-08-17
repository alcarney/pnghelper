#include "png_data.h"

/*
 * This function initialises the PNGImage struct for us in future it may be
 * a good idea to make use of stdarg.h and add a ... argument that allow us
 * to specify optional arguments such as image height and width etc.
 */
PNGImage new_png_image()
{
    PNGImage img;

    // I think we can just initialise everything to zero
    img.width = 0;
    img.height = 0;
    img.color_type = 0;
    img.bit_depth = 0;
    img.number_of_passes = 0;

    // It's good practice to initialise pointers to NULL
    img.png_ptr = NULL;
    img.info_ptr = NULL;
    img.row_pointers = NULL;
    
    return img;
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
