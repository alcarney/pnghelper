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
typedef png_byte* Pixel;
typedef void (*PixelIterator) (Pixel, unsigned int, unsigned int, void*);

// Function Prototypes

/*
 * Given an image and a function pointer to a pixel iterator type
 * function this will automatically loop through each pixel in an image
 * and apply the PixelIterator to it.
 */
void png_pixel_iterate(PNGImage* img, PixelIterator iter, void* params);
//bool get_neighbours(PNGImage* img, unsigned int x, unsigned int y, Pixel* neighbours, int* num_neighbours);

#endif
