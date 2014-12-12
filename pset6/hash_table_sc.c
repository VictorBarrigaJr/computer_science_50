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
hash_table_t *create_hash_table(int size);

/* the function runs data through a hash function and returns a hash value. It 
   accepts two arguments: 1) a pointer to a hash table. 2) a pointer to a char 
   type string */
unsigned int hash(hash_table_t *hashtable, char *str);

/* the function does a string look up by hasing the string, going to the correct
   index in the array, and then doing a linear search on the linked list that
   resides there. It accepts two arguments: 1) a pointer to a hash table. 2) a 
   pointer to a char type string */
list_t *lookup_string(hash_table_t *hashtable, char *str);

/* the function inserts a string by hashing the string and then going into the 
   correct index in the array to insert the new string at the beginning. It 
   accepts two arguments: 1) a pointer to a hash table. 2) a 
   pointer to a char type string. */
int add_string(hash_table_t *hashtable, char *str);

/* the function deletes a table by freeing up the memory used. It accepts one 
   argument: 1) a pointer toi a hash table. */
void free_table(hash_table_t *hashtable);

