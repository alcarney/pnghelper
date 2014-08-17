/*
 * This file contains all the function prototypes required for writing png files
 * any supplimentary data structures will also be defined here
 */

#ifndef PNG_WRITER_C
#define PNG_WRITER_C

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "png_data.h"

// Function Prototypes
bool write_png_to_file(PNGImage* img, char* filename);

#endif
