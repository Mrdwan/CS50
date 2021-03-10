#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

bool isLetter(char character);

int main(void)
{
    string text = get_string("Text:");
    int textCount = strlen(text);
    int letters = 0;
    int words = 0;
    int sentences = 0;
    bool isWord = false;
    bool isSentence = false;

    for (int i = 0; i < textCount; i++)
    {
        if (isLetter(text[i]))
        {
            if (text[i] == ',')
            {
                printf("fuck");
            }
            // false means that this is the start of a new word
            if (!isWord)
            {
                isWord = true;
                words++;
            }

            // false means that this is the start of a new sentence
            if (!isSentence)
            {
                isSentence = true;
                sentences++;
            }

            letters++;
        }
        else if (isspace(text[i]))
        {
            // new word begins if it's white space
            isWord = false;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            // new sentence begins if it's the above marks
            isSentence = false;
        }
    }

    // printf("letters: %i\n", letters);
    // printf("words: %i\n", words);
    // printf("sentences: %i\n", sentences);

    float L = ((float) letters / words) * 100;
    float S = ((float) sentences / words) * 100;

    // printf("L: %f\n", L);
    // printf("S: %f\n", S);

    float index = round((0.0588 * L) - (0.296 * S) - 15.8);

    // printf("index: %i\n", index);

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int) index);
    }
}

bool isLetter(char character)
{
    if (isalpha(character))
    {
        return true;
    }

    return false;
}