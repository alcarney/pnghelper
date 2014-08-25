#include "pixel_ops.h"

/*
 * This function loops over every pixel in the image and calls the given 
 * fuction passing each pixel as an argument.
 *
 * TODO: Add a void pointer argument to allow these PixelIterators to give
 * them selves arguments
 */
void png_pixel_iterate(PNGImage* img, PixelIterator iter)
{
    // We need a check to confirm if we have a valid image
    // If we don't then just print a warning message that nothing was done
    if (is_img_writeable(img))
    {
        // We use these to index the pixel coordintates in the image
        unsigned int x = 0;
        unsigned int y = 0;

        for(y = 0; y < img->height; y++)
        {
            // Get a pointer to the current row
            png_byte* row = img->row_pointers[y];
            
            for(x = 0; x < img->width; x++)
            {
                // Process the pixel
                iter(&(row[x * img->num_color_channels]));
            }
        }
    }
    else
    {
        fprintf(stderr, "[pixel_iterator]: WARN: Image given wasn't valid so nothing was done\n");
    }
}
