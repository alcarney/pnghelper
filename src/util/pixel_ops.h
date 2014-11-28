/*
 * The idea of a pixel iterator is to allow users to provide a function that will be
 * performed on every pixel in the image it's applied to allowing us to abstract away
 * the code required to loop through each pixel in an image
 */

#ifndef PIXEL_OPS_C
#define PIXEL_OPS_C

#include <stdlib.h>
#include <stdio.h>

#include "../png_data.h"

// Data Structures
typedef enum pixel_loc
{
    MIDDLE,
    TOP_EDGE,
    BOTTOM_EDGE,
    LEFT_EDGE,
    RIGHT_EDGE,
    TOP_LEFT_CORNER,
    TOP_RIGHT_CORNER,
    BOTTOM_LEFT_CORNER,
    BOTTOM_RIGHT_CORNER,
    INVALID_LOCATION
} PixelLocation;

typedef png_byte* Pixel;
typedef void (*PixelIterator) (Pixel, unsigned int, unsigned int, void*);

// Function Prototypes

void png_pixel_iterate(PNGImage* img, PixelIterator iter, void* params);
PixelLocation get_pixel_location(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
bool get_neighbours(PNGImage* img, unsigned int x, unsigned int y, Pixel* neighbours, int* num_neighbours);

#endif
