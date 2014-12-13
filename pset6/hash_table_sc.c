 /******************************************************************************
 * 
 * File:    hash_table_sc.c
 *
 * Victor Barriga
 * victorbarriga@live.com
 *
 * Implements a hash table that stores strings, and handles collisions by using
 * separate chaining.
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "shared_macros.h"
#include "hash_table_sc.h"

/***
 * Functions
 **/

/* the function returns a hash table. It accepts one argument: 1) an int to 
   create the size */
hash_table_t *create_hash_table(int size)
{
    hash_table_t *new_table;
    // invalid size for table
    if (size < 1)
    {
        return NULL;
    }

    // allocate memory for table structure
    if ((new_table = malloc(sizeof(hash_value_t))) == NULL)
    {
        return NULL;
    }

    // allocate memory for table
    if ((new_table->table = malloc(sizeof(list_t *) * size)) == NULL)
    {
        return NULL;
    }

    // initialize the elements of the table
    for (i = 0; i < size; i++) 
    {
        new_table->table[i] = NULL;
    }

    // set the table's size
    new_table->size = size;

    return new_table;
}


/* the function runs data through a hash function and returns a hash value. It 
   accepts two arguments: 1) a pointer to a hash table. 2) a pointer to a char 
   type string */
unsigned int hash(hash_table_t *hashtable, char *str)
{
    unsigned int hashval;
    // initial hash 0
    hashval = 0;
    
    /*for each character, we multiply old hash by 31 and add the current 
      character (shifting a number left is equivalent to multiplying it by 2 
      raise to the number of places shifted). We are multiplying hashval by 32 
      and then subtracting hashval, because shifting and subtraction are much 
      more efficient operations than multiplication. faster! */
    for (; *str != '\0'; str++) 
    {
        hashval = *str +(hashval << 5) - hashval;
    }
    
    // returns the hash value mod the hashtable size so it will fit within range
    return hashval % hashtable->size;
}


/* the function does a string look up by hasing the string, going to the correct
   index in the array, and then doing a linear search on the linked list that
   resides there. It accepts two arguments: 1) a pointer to a hash table. 2) a 
   pointer to a char type string */
list_t *lookup_string(hash_table_t *hashtable, char *str)
{
    list_t *list;
    unsigned int hashval = hash(hashtable, str);

    /* goes to the appropriate index based on hash value and checks if str is 
       in the list. If it is, it returns a pointer to the list element. If it 
       isn't it returns NULL. */
    for (list = hashtable->table[hashval]; list != NULL; list->next) 
    {
        if (strcmp(str, list->str) == 0)
        {
            return list;
        }
    }

    return NULL;
}


/* the function inserts a string by hashing the string and then going into the 
   correct index in the array to insert the new string at the beginning. It 
   accepts two arguments: 1) a pointer to a hash table. 2) a 
   pointer to a char type string. */
int add_string(hash_table_t *hashtable, char *str)
{
    list_t *new_list;
    list_t *current_list;
    unsigned int hashval = hash(hashtable, str);

    // allocate memory for list
    if ((new_list = malloc(sizeof(list_t))) == NULL)
    {
        return 1;
    }

    // does the item already exist?
    current_list = lookup_string(hashtable, str);

    // if item does exist do not insert again
    if (current_list != NULL)
    {
        return 2;
    }

    // insert item into list
    new_list->str = strdup(str);
    new_list->next = hashtable->table[hashval];
    hashtable->table[hashval] = new_list;

    return 0;
}


/* the function deletes a table by freeing up the memory used. It accepts one 
   argument: 1) a pointer toi a hash table. */
void free_table(hash_table_t *hashtable)
{
    int i;
    list_t *list, *temp;

    if (hashtable == NULL)
    {
        return;
    }

    // free the memory for every item in the table, including all strings
    for (i = 0; i < hashtable; i++) 
    {
        list = hashtable->table[i];
        while (list != NULL) 
        {
            temp = list;
            list = list->next;
            free(temp->str);
            free(temp);
        }
    }

    // free the table
    free(hashtable->table);
    free(hashtable);
}
