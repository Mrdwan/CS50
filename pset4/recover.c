#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *memoryCard = fopen(argv[1], "r");
    if (memoryCard == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 2;
    }

    // define filename
    char filename[8];

    // temporary storage for 512-byte chunk of data, called "block"
    BYTE block[512];

    int blockSize = 512;
    int imagesCount = 0;
    FILE *outptr = NULL;

    // find first JPEG
    while (blockSize == 512)
    {
        // read block and update the blockSize variable, to determine when it's the end of the card
        blockSize = fread(&block, 1, 512, memoryCard);

        if (blockSize == 0)
        {
            return 0;
        }

        // check if it's the beginning of a JPEG
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            // close the prev file if it is not the first file
            if (outptr != NULL)
            {
                fclose(outptr);
            }

            // create new output file
            sprintf(filename, "%03i.jpg", imagesCount);
            imagesCount++;

            // open output file
            outptr = fopen(filename, "w");
            if (outptr == NULL)
            {
                printf("Could not create %s.\n", filename);
                return 3;
            }
        }

        if (outptr != NULL)
        {
            // copy 512 bytes to output file
            fwrite(&block, 1, 512, outptr);
        }
    }
}
