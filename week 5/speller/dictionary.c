// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "dictionary.h"
#include <strings.h>
#include<string.h>
//unsigned int = ein Integer der niemals negativ sein kann
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];//Jede node besteht also aus einem Wort
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];
bool check(const char *word)
{
    int index = hash(word);
    node* curser = table[index];
    while (curser != NULL)
    {
        if (strcasecmp(curser -> word, word)==0)
        {
            return true;
        }
        curser = curser -> next;
    }
    return false;//word was not found in dictonary
}//sollte funktionieren

// Hashes word to a number
unsigned int hash(const char *word)
{
    if (isalpha(word[0]) == false)
    {
        return 1;
    }
    if (toupper(word[0]) - 'A' > N)
    {
        return (toupper(word[0]) - 'A') % N;
    }
    return toupper(word[0]) - 'A';
}


//load data into memory, return true if successful, else false
bool load(const char *dictionary)
{
    char word[LENGTH + 1];
    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        printf("File failed to load");
        fclose(input);
        return false;
    }
    //FILE *output = fopen();
    while (fscanf(input, "%s",word) != EOF)//read from the file
    {

        if (strlen(word) > LENGTH)
        {
           return false;
        }
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("not enough memory");
            return false;
        }
        strcpy(new_node -> word, word);
        new_node -> next = NULL;

        int index = hash(word);
        if (table[index] == NULL)//if no list was yet created
        {
            table[index] = new_node;
        }
        else
        {
            new_node -> next = table[index];
            table[index] = new_node;
        }

    }
    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int word_count = 0;//each word represents a node
    for (int i = 0; i < N; i++)
    {
        for (node *ptr = table[i]; ptr != NULL; ptr = ptr -> next)
        {
            word_count = word_count + 1;
        }
    }
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N ; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor -> next;
            free(tmp);
        }
    }
    return true;
}
