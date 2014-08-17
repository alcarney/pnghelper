/*
 * This file declares all the data structures used by the library and the functions used to
 * manipulate them, mainly initialising the data structures and clearing up any dynamically 
 * allocated memory used by them.
 */
#ifndef PNG_DATA_C
#define PNG_DATA_C

#include <png.h>

#define PNG_DEBUG 3

/*
 *             Things that may be good for future reference:
 *
 *  -> png_byte is just an unsigned char
 */

// Data Structures

typedef struct pngimg
{
    unsigned int with;
    unsigned int height;
    png_byte color_type;
    png_byte bit_depth;

    png_structp png_ptr;
    png_infop info_ptr;

    // Not sure what this does but I think it may be something to do with interlacing
    int number_of_passes;
    png_bytep row_pointers;
} PNGImage;

// Function Prototypes
PNGImage new_png_image();
void destroy_png_image(PNGImage* img);

#endif
