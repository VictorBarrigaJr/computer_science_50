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
typedef struct _list_t_
{
    char *string; // data type 
    struct _list_t_ *next; // pointer to next node 
} list_t;

/* structure for hash table  - using dynamic array*/
typedef struct _hash_table_t_
{
    int size; // size of the table
    list_t **table; // the table elements
} hash_table_t; 

/***
 * Functions
 **/

/*

#endif
