 /******************************************************************************
 * 
 * File:    hash_table_sc.h
 *
 * Victor Barriga
 * victorbarriga@live.com
 *
 * A hash table stores a set of values which can be addressed by a key. Given
 * the key, the corresponding value can be looped up quickly. Hash tables allow
 * storage and retrieval of data in an average time of O(1).
 *
 * This file declares a hash table that stores strings, and handles collisions 
 * by using separate chaining.
 *
 * The basic operations needed to perform a hash table are: 1) We need to be 
 * able to create a table. 2) We need to be able to hash; thus we need a hash
 * function. 3) We need to be able to free a table. 4) We need to be able to 
 * insert into them. 5) We need to be able to loop up an element in them.
 *
 ******************************************************************************/

#ifndef HASH_TABLE_SC_H
#define HASH_TABLE_SC_H

#include "shared_macros.h"

/***
 * Data structures
 **/

/* stucture for singly linked list - for separate chaining */
typedef struct _list_t_ list_t;

/* structure for hash table  - using dynamic array*/
typedef struct _hash_table_t_ hash_table_t; 

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
   accepts two arguments: 1) a pointer to a hash table. 2) a pointer to a char 
   type string. */
int add_string(hash_table_t *hashtable, char *str);


/* the function deletes a table by freeing up the memory used. It accepts one 
   argument: 1) a pointer toi a hash table. */
void free_table(hash_table_t *hashtable);


/* the function removes a string from the hash table. It accepts two arguments: 
   1) a pointer to a hash table. 2) a pointer to a char type string */
int delete_string(hash_table_t *hashtable, char *str);


/* the function counts the number ot strings stored in the hash table. It 
   accepts one argument: 1) a pointer to a hash table. */
int count_strings(hash_table_t *hashtable); 


#endif
