/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>

#include "dictionary.h"
#include "hash_table_sc.c"
#include "shared_macros.c"

/***
 * Global variables
 **/

// hash table for storing dictionary
hash_table_t *dict_hash_table;
// int to keep count of total words in dictionary
int word_count = 0;

/***
 * Functions
 **/
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open dictionary to RAM
    FILE *fptr = fopen(dictionary, "r");
    // rerurns false if dictionary is empty.
    if (fptr == NULL)
    {
        printf("Error loading dictionary file to ptr.\n");
        return false;
    }

    // create hash table with NULL's
    dict_hash_table = create_hash_table(HASH_TABLE_SIZE);
    
    // reads from the dictionary fptr , hashes and adds to hash table
    char dict_word_buffer[LENGTH + 1]; 
    while (fscanf(fptr, "%s\n", dict_word_buffer) != EOF) 
    {
        // prepend word to hash table & count total words
        add_string(dict_hash_table, dict_word_buffer);
        word_count++;        
    }

    fclose(fptr);

    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}
