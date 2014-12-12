 /******************************************************************************
 * 
 * File:    hash_table_sc.h
 *
 * Victor Barriga
 * victorbarriga@live.com
 *
 * Declares a singly linked list is a list in  
 * Implements a hash table that stores strings, and handles collisions by using
 * separate chaining.
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

/* structure for hash table */
typedef struct _hash_table_t_
{
    int size; // size of the table
    list_t **table; // the table elements
} hash_table_t; 

#endif
