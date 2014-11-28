#include "pixel_ops.h"

// Private Data Structures

// Private Static Function Prototypes

// Private static functions

/*
 * Given an coordinate, and the image dimensions this function determines where on the image the pixel is
 * so that we can then handle it appropriately in get_neighbours
 *
 * Arguments:
 *              x: Pixel's x coordinate
 *              y: Pixel's y coordinate
 *              width: The width of the image
 *              height: The height of the image
 */
PixelLocation get_pixel_location(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
    // Quick check to make sure that the point (x,y) is actually within the image
    if(x > width || y > height)
        return INVALID_LOCATION;

    // If y is zero then we are on the top edge...
    if (y == 0)
    {
        // But are we in the left corner?
        if (x == 0)
            return TOP_LEFT_CORNER;

        // Or are we in the right corner?
        if (x == (width - 1))
            return TOP_RIGHT_CORNER;

        // No then we must be on the top edge
        return TOP_EDGE;
    }

    // If y is equal to the height then we must be at the bottom of the image
    if (y == (height - 1))
    {
        // But are we in the left corner?
        if (x == 0)
            return BOTTOM_LEFT_CORNER;

        // Or are we in the right hand corner
        if (x == (width - 1))
            return BOTTOM_RIGHT_CORNER;

        // No then we must be on the bottom edge
        return BOTTOM_EDGE;
    }

    // If we get this far then the y coordinate is not on the edge of the image so now we only
    // need to check if x in an extremity of the image
    if (x == 0)
        return LEFT_EDGE;

    if (x == (width - 1))
        return RIGHT_EDGE;

    // If we get this far then we must be in a middle case
    return MIDDLE;
}

/*
 * This function loops over every pixel in the image and calls the given
 * fuction passing each pixel as an argument.
 *
 * TODO: Add a void pointer argument to allow these PixelIterators to give
 * them selves arguments
 */
void png_pixel_iterate(PNGImage* img, PixelIterator iter, void* params)
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
                iter(&(row[x * img->num_channels]), x, y, params);
            }
        }
    }
    else
    {
        fprintf(stderr, "[pixel_iterator]: WARN: Image given wasn't valid so nothing was done\n");
    }
}

/*
 * Given the coordinates of a pixel get all of its neighbours in its surrounding area
 *
 * TODO: This current implementation means that the relative position of the returned pixels
 * are lost in some cases it may be useful to have this data so improve this to give the option
 * to preserve this data
 */
/*bool get_neighbours(PNGImage* img, unsigned int x, unsigned int y, Pixel* neighbours, int* num_neighbours)
{
    *
     * So as breifly mentioned above the purpose of this function is to return
     * an array of pixels that are 'neighbours' for the given pixel coordinates.
     * The most common case would be a pixel that is 'in the middle' of an image,
     * and would look something like this: (Case A)
     *
     *                  x, x, x
     *                  x, o, x
     *                  x, x, x
     *
     *  Where 'o' is the given pixel and 'x' represents a neighbour
     *
     *  However there are a number of ... edge cases to consider - see what I did there? ;)
     *  Such as:
     *
     *      o,x     x,o     x,x     x,x
     *      x,x     x,x     o,x     x,o
     *
     *  The corner cases (Case B) and,
     *
     *      x,x     x,o,x   x,x,x   x,x
     *      o,x     x,x,x   x,o,x   x,o
     *      x,x                     x,x
     *
     *  The literal edges of the image (Case C).
     *
     *  So as you can see we cannot blindly apply the obvious method for the original case 
     *  otherwise we will be returning pixels that are no where near the actual pixel at best
     *  and at worst accessing memory we have no right to and causing all sorts of problems, so
     *

    *
     * So let's start with a few sainty checks
     *

    // Check that the image is valid
    if(!is_img_writeable(img))
    {
        fprintf(stderr, "[get_neighbours]: ERROR: Image given is not valid\n");
        return false;
    }

    // Check that the coordinates are within the image bounds
    if(x > img->width || y > img->height)
    {
        fprintf(stderr, "[get_neighbours]: ERROR: Coordinates given out of bounds of the given image\n");
        return false;
    }

    *
     * Now we need to determine what case we are dealing with so let's use a helper
     * function and a switch statement
     *
    switch(get_pixel_location(x, y, img->width, img->height))
    {
        default:
            fprintf(stderr, "[get_neighbours]: ERROR: Unable to determine case type\n");
            return false;
    }

}*/
