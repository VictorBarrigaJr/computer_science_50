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
#include <ctype.h>
#include <math.h>

#include "dictionary.h"


/**
 * Data structure for singly linked list - for separate chaining.
 */
typedef struct sll_node
{
    char word[LENGTH + 1]; // data type
    struct sll_node *next; // pointer to next node in list
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
    unsigned int hashval;
    // initial hash 0
    hashval = 0;
    
    /*for each character, we multiply old hash by 31 and add the current 
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
 * function prepends node to the beginning of a linked list. function accepts
 * one argument: 1) an char word, which is the new data int for the new node.
 */
void new_entry_prepend(/*sll_node *hashtable,*/char *word)
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
    //new->word = word;
    
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
    
    // find the correct hash index for word loop
    int index = hash(unchecked_word);
    
    // returns false, word is not in dictionary
    if (hashtable[index] == NULL)
    {
        // index is empty, so word not in dictionary
        return false;
    }
    else
    {
        /* creates temp node to iterate through linked list at index location,
           then compares word with uncheckword for match, returns true is 
           spelled correctly, otherwise false. */
        sll_node *list_iterator = hashtable[index];
        
        // traverse dictionary while not NULL
        while (list_iterator->next != NULL)
        {
            if (strcmp(unchecked_word, list_iterator->word) == 0)
            {
                return true;
            }
            list_iterator = list_iterator->next;
        }
       
        if (strcmp(unchecked_word, list_iterator->word) == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
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
    
    /* reads from dictionary fptr, assumes all words are lowercase, hashes word, 
       and adds to appropriate hash table index linked list. */
    while (fgets(word_buffer, LENGTH + 2, fptr))
    {
        // inserts string terminator NULL
        word_buffer[strlen(word_buffer) - 1] = '\0';
        /*
        // lowercase for word
        for (int i = 0, n = strlen(word_buffer); i < n; i++)
            word_buffer[i] = tolower(word_buffer[i]);
        */
        /*
        // copy word into temp sll_node
        sll_node *temp = malloc(sizeof(sll_node));
        strncpy(temp->word, word_buffer, LENGTH + 1);
        temp->next = NULL;
        
        // update the sll_node into the correct place
        int index = hash(word_buffer);
        
        if (hashtable[index] == NULL)
        {
            hashtable[index] = temp;
        }
        else
        {
            // loop through the linked list and insert it into the table
            sll_node *list_iterator = hashtable[index];

            while(list_iterator->next != NULL)
            {
                list_iterator = list_iterator->next;
            }
            
            // assign the sll_node to the last of the linked list
            list_iterator->next = temp;
        }
        */
        new_entry_prepend(word_buffer);
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
    /*
    // initialize dictionary's size
    unsigned int size = 0;
    
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        if (hashtable[i] != NULL)
        {
            size++;
            for(sll_node* list_iterator = hashtable[i]; list_iterator->next != NULL; list_iterator = list_iterator->next)
                size++;
        }
        }
        return size;*/    
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
        sll_node* first = hashtable[i];
        while (first != NULL)
        {
            sll_node* next = first->next;
            free(first);
            first = next;
        }
    }
    
    return true;
}
