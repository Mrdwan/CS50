// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];
int wordsSize = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int hashIndex = hash(word);
    if (table[hashIndex] == NULL)
    {
        return false;
    }

    node *currentNode = table[hashIndex];

    while(currentNode != NULL)
    {
        if (strcasecmp(currentNode->word, word) == 0)
        {
            return true;
        }

        currentNode = currentNode->next;
    }

    free(currentNode);

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int characterAsInt = 97; // 97 == "a"
    int firstLetterAsInt = (int) tolower(word[0]);

    while (firstLetterAsInt != characterAsInt)
    {
        characterAsInt++;
    }

    return characterAsInt - 97; // return index of 0 to 25, so we subtract 97
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // declare a word var
    char word[LENGTH + 1];

    // scan the loaded file and read it
    while (fscanf(file, "%s", word) != EOF)
    {
        // use hash (takes a string and returns an index)
        int hashIndex = hash(word);

        // use malloc
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        // copy word into node using strcpy
        strcpy(n->word, word);
        n->next = NULL;

        // update the list
        if (table[hashIndex] != NULL)
        {
            n->next = table[hashIndex];
        }
        table[hashIndex] = n;

        // increase words size by one
        wordsSize++;
    }


    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordsSize;
}

// destroy one node
void destroy(node *head)
{
    if (head->next != NULL)
    {
        destroy(head->next);
    }

    free(head);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            destroy(table[i]);
        }
    }

    return true;
}
