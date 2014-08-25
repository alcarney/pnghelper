/*
 * This file declares all the data structures used by the library and the functions used to
 * manipulate them, mainly initialising the data structures and clearing up any dynamically 
 * allocated memory used by them.
 */
#ifndef PNG_DATA_C
#define PNG_DATA_C

#include <stdlib.h>
#include <stdbool.h>
#include <png.h>

#define PNG_DEBUG 3

// Let's define some aliases for png colour types so we don't have to type as much
#define GRAYSCALE PNG_COLOR_TYPE_GRAY
#define RGB PNG_COLOR_TYPE_RGB
#define RGBA PNG_COLOR_TYPE_RGB_ALPHA

/*
 *             Things that may be good for future reference:
 *
 *  -> png_byte is just an unsigned char
 */

// Data Structures

typedef struct pngimg
{
    unsigned int width;
    unsigned int height;
    unsigned int num_channels;
    png_byte color_type;
    png_byte bit_depth;

    png_structp png_ptr;
    png_infop info_ptr;

    // Not sure what this does but I think it may be something to do with interlacing
    int number_of_passes;
    png_bytep* row_pointers;
} PNGImage;

typedef struct imgparams
{
    unsigned int width;
    unsigned int height;
    png_byte color_type;
} IMGParams;

// Function Prototypes
bool new_png_image(PNGImage* img, IMGParams* params);
bool is_empty_img_struct(PNGImage* img);
bool is_img_writeable(PNGImage* img);

int get_num_channels(PNGImage* img);

void destroy_png_image(PNGImage* img);

#endif
