#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define GRAYSCALE_CHANNEL 1
#define SHADER_COUNT 7

int my_ceil(double a) { return (a - (int)a > 0)? (int)a+1 : a; }

int main(int argc, char** argv) {
    assert(argc >= 2);

    int width, height, channels;
    int desiredch = GRAYSCALE_CHANNEL;

    // DARKER --> LIGHTER
    char shades[SHADER_COUNT] =
        { '%', '%', '=', '~', '.', '.', ' ' };

    stbi_uc *img = stbi_load(
            argv[1],
            &width,
            &height,
            &channels,
            desiredch);
    assert(img != NULL);

    int divisor = my_ceil((double)UINT8_MAX/SHADER_COUNT);
    int total_values = width * height * desiredch;

    for (int i = 0; i < total_values; i += desiredch) {
        if (i!=0 && i%width==0) printf("\n");
        printf("%c", shades[img[i]/divisor]);
    }

    stbi_image_free(img);

    return 0;
}
