#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // get out
    if (argc > 2 || argc < 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int num = atoi(argv[1]);
    int argcCount = strlen(argv[1]);

    // check if all int
    for (int i = 0; i < argcCount; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // check if only positive numbers
    if (num <= 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string text = get_string("plaintext: ");
    int count = strlen(text);

    for (int i = 0; i < count; i++)
    {
        // if upper
        if (isalpha(text[i]) && isupper(text[i]))
        {
            text[i] = (char)(((text[i] - 64) + num) % 26) + 64;
        }
        else if (isalpha(text[i]) && islower(text[i]))
        {
            text[i] = (char)(((text[i] - 96) + num) % 26) + 96;
        }
    }

    // print and return
    printf("ciphertext: %s\n", text);
    return 0;
}