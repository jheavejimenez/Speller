// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;
unsigned int numberOfwords = 0;
// Number of buckets in hash table
const unsigned int N = 1000;

// Hash table
node *hashtable[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    char check_word[strlen(word)];
    strcpy(check_word, word);
    for (int i = 0; check_word[i] != '\0'; i++)
    {
        check_word[i] = tolower(check_word[i]);
    }
    int index = hash(check_word);
    if (hashtable[index] != NULL)
    {
        for (node *nodePointer = hashtable[index]; nodePointer != NULL; nodePointer = nodePointer -> next)
        {
            if (strcmp(nodePointer -> word, check_word) == 0)
            {
                return true;
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    int hash = 0;
    int n;
    
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (isalpha(word[i]))
        {
            n = word[i] - 'a' + 1;
        }
        else
        {
            n = 27;
        }
        hash = ((hash << 3) + n) % N;
    }
    return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    //safety check
    if (file == NULL)
    {
        return false;
    }
    //Hashtable
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }
    char word[LENGTH + 1];
    node *new_nodePointer;
    
    while (fscanf(file, "%s", word) != EOF)
    {
        numberOfwords ++;
        do
        {
            new_nodePointer = malloc(sizeof(node));
            if (new_nodePointer == NULL)
            {
                free(new_nodePointer);
            }
        }
        while (new_nodePointer == NULL);
        
        //copy the word into the node
        strcpy(new_nodePointer -> word, word);
        int index = hash(word);
        
        new_nodePointer -> next = hashtable[index];
        hashtable[index] = new_nodePointer;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return numberOfwords;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    
    for (int i = 0; i < N; i++)
    {
        node *pointer = hashtable[i];
        while (pointer != NULL)
        {
            node *new_pointer = pointer;
            pointer = pointer -> next;
            free(new_pointer);
            
        }
    }
    return true;
}
