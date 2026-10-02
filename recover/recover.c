#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int BLOCK = 512;

bool is_header(uint8_t b[]);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("The file cannot be opened: Error\n");
        return 1;
    }

    uint8_t buffer[BLOCK];

    int image_count = 0;
    char filename[8];
    FILE *img = NULL;

    while (fread(buffer, 1, BLOCK, card) == BLOCK)
    {
        if (is_header(buffer))
        {
            if (img != NULL)
            {
                fclose(img);
            }

            sprintf(filename, "%03i.jpg", image_count++);
            img = fopen(filename, "w");
        }
        if (img != NULL)
        {
            fwrite(buffer, 1, BLOCK, img);
        }
    }

    if (img != NULL)
    {
        fclose(img);
    }

    fclose(card);
}

bool is_header(uint8_t b[])
{
    if (b[0] == 0xff && b[1] == 0xd8 && b[2] == 0xff && (b[3] & 0xf0) == 0xe0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
