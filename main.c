#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define GRAYSCALE_CHANNEL 1
#define SHADES_COUNT 7

typedef enum {
    NONE      = 0,
    INVERT    = 1,
    REVERSE   = 2,
} Flags;

int my_ceil(const double a) { return (a - (int)a > 0)? (int)a+1 : a; }
int my_floor(const double a) { return (int)a; }

int main(int argc, char** argv) {
    assert(argc >= 2);

    Flags flags = NONE;

    char opt;
    while((opt = getopt(argc, argv, "ir")) != -1)
    {
        switch(opt)
        {
            case 'i':
                flags |= INVERT;
                break;
            case 'r':
                flags |= REVERSE;
                break;
        }
    }

    assert(optind < argc);

    int width, height, channels;
    int desiredch = GRAYSCALE_CHANNEL;

    // DARKER --> LIGHTER
    char shades[SHADES_COUNT] =
        { '%', '%', '=', '~', '.', '.', ' ' };

    if (flags & REVERSE) {
        for (int i = 0; i < my_floor((double)SHADES_COUNT/2); ++i) {
            const char temp = shades[i];
            shades[i] = shades[SHADES_COUNT-i-1];
            shades[SHADES_COUNT-i-1] = temp;
        }
    }

    stbi_uc *img = stbi_load(
            argv[optind],
            &width,
            &height,
            &channels,
            desiredch);
    assert(img != NULL);

    int total_values = width * height * desiredch;

    if (flags & INVERT) {
        for (int i = 0; i < total_values; i += desiredch) {
            img[i] = 0xFF - img[i];
        }
    }

    int divisor = my_ceil((double)UINT8_MAX/SHADES_COUNT);

    for (int i = 0; i < total_values; i += desiredch) {
        if (i!=0 && i%width==0) printf("\n");
        printf("%c", shades[img[i]/divisor]);
    }

    stbi_image_free(img);

    return 0;
}
