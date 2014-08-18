/*
 * This test is the one given on the example I have been working from, where it removes all red from an image 
 * and equate the blue and green channels
 */

#include "../src/png_reader.h"
#include "../src/png_writer.h"

bool process_file(PNGImage* img)
{
    // We want to make sure the image we use is of color_type RGBA
    if (png_get_color_type(img->png_ptr, img->info_ptr) == PNG_COLOR_TYPE_RGB)
    {
        fprintf(stderr, "[process_file]: ERROR: The image is not of type RGBA\n");
        return false;
    }

    if(png_get_color_type(img->png_ptr, img->info_ptr) != PNG_COLOR_TYPE_RGBA)
    {
        fprintf(stderr, "[process_file]: ERROR: The image is not of type RGBA\n");
        return false;
    }

    unsigned int i = 0;
    unsigned int j = 0;

    // Now we loop through each pixel and change the colours
    for(i = 0; i < img->height ; i++)
    {
        png_byte* row = img->row_pointers[i];

        for(j = 0; j < img->width ; j++)
        {
            png_byte* pixel = &(row[j*4]);
            printf("Pixel at [%d,%d] has RGBA values: %d, %d, %d, %d\r", i, j,
                    pixel[0], pixel[1], pixel[2], pixel[3]);

            pixel[0] = 0;
            pixel[1] = pixel[2];
        }
    }

    puts("\n");

    return true;
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: test <input> <output>\n");
        return 1;
    }

    PNGImage img = new_png_image();

    if(!read_png_from_file(&img, argv[1]))
    {
        destroy_png_image(&img);
        return 1;
    }

    if(!process_file(&img))
    {
        destroy_png_image(&img);
        return 1;
    }

    if(!write_png_to_file(&img, argv[2]))
    {
        destroy_png_image(&img);
        return 1;
    }

    destroy_png_image(&img);
    return 0;
    
}
