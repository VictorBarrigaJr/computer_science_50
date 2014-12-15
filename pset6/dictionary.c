/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

/**
 * Data structure for singly linked list - for separate chaining.
 */
typedef struct sll_node
{
    char word[LENGTH + 1]; // data type
    struct sll_node *next; // pointer to next sll_node in list
}
// create an initial linked list
sll_node;

// create hash table of linked lists, initialized to NULL.
sll_node *hashtable[HASH_TABLE_SIZE] = {NULL};

// counter to track total words in dictionary
int word_count = 0;

/**
 * Returns a hash value to index into hash table.
 */
int hash(char* word)
{
    unsigned int hashval = 0;
    
    /*for each character, we multiply old hash by 31 and add the current_node 
      character (shifting a number left is equivalent to multiplying it by 2 
      raise to the number of places shifted). We are multiplying hashval by 32 
      and then subtracting hashval, because shifting and subtraction are much 
      more efficient operations than multiplication. faster! */
    for (; *word != '\0'; word++) 
    {
        hashval = *word +(hashval << 5) - hashval;
    }
    
    // returns the hash value mod the hashtable size so it will fit within range
    return hashval % HASH_TABLE_SIZE;
}

/**
 * function prepends sll_node to the beginning of a linked list. function accepts
 * one argument: 1) an char word, which is the new data int for the new sll_node.
 */
void new_entry_prepend(char *word)
{
    // create new list entry
    sll_node *new = malloc(sizeof(sll_node));
    if (new == NULL)
    {
        printf("Error -- out of memory\n");
        exit(1);
    }
    strncpy(new->word, word, LENGTH + 1);
    new->next = NULL;
        
    // update ssl_node into correct index
    int index = hash(word);

    // insert into the start of list
    if (hashtable[index] == NULL)
    {
        hashtable[index] = new;
        new->next = NULL;
    }
    else
    {
        new->next = hashtable[index];
        hashtable[index] = new;
    }        
}

/**
 * Returns true if a sll_node in the list contains the value i and false
 * otherwise.
 */
bool node_lookup(char *word)
{
    
    // find the correct hash index for word loop
    int index = hash(word);

    sll_node *check_node = hashtable[index];
    
    while (check_node != NULL)
    {
        // Case-insensitive comparing
        if (!(strcasecmp(word, check_node->word)))
        {
            return true;
        }    
        check_node = check_node->next;
    }    
    return false;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // word to check from text
    char unchecked_word[LENGTH + 1];
    int word_len = strlen(word);
    
    // copy and convert word into unchecked_word in lowercase
    for (int i = 0; i < word_len; i++)
    {
        unchecked_word[i] = tolower(word[i]);
    }
    // insert null char into copied word
    unchecked_word[word_len] = '\0';
   
    return node_lookup(unchecked_word);
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{ 
    // load dictionary to the memory
    FILE *fptr = fopen(dictionary, "r");
    if (fptr == NULL)
    {
        printf("Error - unable to load dictionary.");
        return false;
    }

    // buffer to temp hold word from dictionary
    char word_buffer[LENGTH + 2];
    
    /* reads from dictionary fptr, assumes all words are lowercase & data in 
       chain will be reverse order, calls new entry prepend function*/
    while (fgets(word_buffer, LENGTH + 2, fptr))
    {
        // inserts string terminator NULL
        word_buffer[strlen(word_buffer) - 1] = '\0';
        // adds new word to hash table
        new_entry_prepend(word_buffer);
        // counts word entries
        word_count++;
    }
    // close the fptr
    fclose(fptr);

    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{      
    return word_count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // loop through the hash and free each linked list
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        sll_node *current_node = hashtable[i];
        while (current_node != NULL)
        {
            sll_node* next_node = current_node->next;
            free(current_node);
            current_node = next_node;
        }
    }    
    return true;
}
