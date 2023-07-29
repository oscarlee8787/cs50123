// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

//word count variable
int wordcount = 0;


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hash_value = hash(word);
    node *cursor = table[hash_value];
    //if cursor is not equal to
    while (cursor != 0)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            //printf("Hi\n");
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    char buffer[LENGTH + 1];
    int hash_value = 0;
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Cannot open dictionary");
        return false;
    }
    while (fscanf(dict, "%s", buffer) != EOF)
    {
        wordcount++;

        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Cannot create n");
            return false;
        }
        strcpy(n->word , buffer);
        hash_value = hash(buffer);
        n->next = NULL;
        n->next = table[hash_value];
        table[hash_value] = n;
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordcount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    int freed = 0;
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while(cursor != NULL)
        {
            node *next = cursor->next;
            free(cursor);
            freed++;
            cursor = next;
        }
        table[i] = NULL;

    }
    if (freed != 0)
    {
        //printf("How many freed: %i\n", freed);
        return true;
    }

    return false;
}
