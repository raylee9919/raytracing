/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Sung Woo Lee $
   $Notice: (C) Copyright 2024 by Sung Woo Lee. All Rights Reserved. $
   ======================================================================== */

#include "stdlib.h"
#include "stdio.h"

#include "ray.h"

internal u32
get_total_pixel_size(Image_U32 image)
{
    u32 result = image.width * image.height * sizeof(u32);
    return result;
}

internal Image_U32
allocate_image(u32 width, u32 height)
{
    Image_U32 image = {};
    image.width = width;
    image.height = height;

    u32 output_pixel_size = get_total_pixel_size(image);
    image.pixels = (u32 *)malloc(output_pixel_size);

    return image;
}

internal void
write_image(Image_U32 image, char *output_file_name)
{
    u32 output_pixel_size = get_total_pixel_size(image);

    Bitmap_Header header = {};
    header.file_type = 0x4D42;
    header.file_size = sizeof(header) * output_pixel_size;
    header.bitmap_offset = sizeof(header);
    header.size = sizeof(header) - 14;
    header.width = image.width;
    header.height = image.height;
    header.planes = 1;
    header.bits_per_pixel = 32;
    header.compression = 0;
    header.size_of_bitmap = output_pixel_size;
    header.horz_resolution = 0;
    header.vert_resolution = 0;
    header.colors_used = 0;
    header.important = 0;

    FILE *out_file = fopen(output_file_name, "wb");
    if (out_file)
    {
        fwrite(&header, sizeof(header), 1, out_file);
        fwrite(image.pixels, output_pixel_size, 1, out_file);
        fclose(out_file);
        printf("*** SUCCESSFUL! ***\n");
    }
    else
    {
        fprintf(stderr, "[ERROR] Unable to write output file %s.\n", output_file_name);
    }
}

int main(int arg_count, char **args)
{
    Image_U32 image = allocate_image(1280, 720);

    u32 *out = image.pixels;
    for (u32 y = 0;
         y < image.height;
         ++y)
    {
        for (u32 x = 0;
             x < image.width;
             ++x)
        {
            *out++ = (y < 32) ? 0xffff0000 : 0xff0000ff;
        }
    }

    write_image(image, "test.bmp");


    return 0;
}
