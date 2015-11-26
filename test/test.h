#pragma once
#include <embreeLib.h>

inline void print_image(
    const std::vector<rt_result>&   image,
    const int                       width,
    const int                       height)
{
    for (int i=0; i<height; ++i) {
        for (int j=0; j<width; ++j)
            printf("%c", image[i*width+j].tri_idx>=0?'*':'.');
        printf("\n");
    }
}

inline void print_image_uv(
    const std::vector<rt_result>&   image,
    const int                       width,
    const int                       height)
{
    for (int i=0; i<height; ++i) {
        for (int j=0; j<width; ++j)
            if (image[i*width+j].tri_idx < 0) continue;
            else
                printf("(%g,%g)\t", image[i*width+j].bary.x, image[i*width+j].bary.y);
        printf("\n");
    }
}
 