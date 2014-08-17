/*
 * This file contains all the function declarations associated with 
 * reading png images into memory, any data structures that aid in this
 * operation will also be defined here
 */

#ifndef PNG_READER_C
#define PNG_READER_C

#include <stdio.h>
#include <stblib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "png_data.h"

// Function Prototypes
bool read_png_from_file(PNGImage* img, char* filename);

#endif
