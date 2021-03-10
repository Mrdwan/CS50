#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;

    do
    {
        height = get_int("height:");
    }
    while (height <= 0 || height >= 9);

    // print height
    for (int i = 1; i <= height; i++)
    {
        // print width first blocks
        for (int j = 1; j <= height; j++)
        {
            if (j > height - i)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }

        // print two empty spaces
        for (int k = 0; k < 2; k++)
        {
            printf(" ");
        }

        // print the last blocks
        for (int l = 1; l <= i; l++)
        {
            printf("#");
        }

        printf("\n");
    }
}