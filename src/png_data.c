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
