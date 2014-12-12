 /******************************************************************************
 * 
 * File:    linked_list.h
 *
 * Victor Barriga
 * victorbarriga@live.com
 *
 * Declares a singly linked list is a list in which each entry contains a 
 * pointer to the preceeding entry in the list as well as a pointer to the next 
 * entry in the list. 
 *
 ******************************************************************************/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "shared_macros.h"

/***
 * Singly linked list typdef
 **/
typedef struct node
{
    // data to store in node (type char string - word)
    char val[LENGTH + 1];
    // pointer to the next node
    struct node* next;
} node;

/***
 * Function returns true if a node in the list contains the value and false 
 * otherwise. Function accepts two arguments: 1) a pointer type node to root 
 * pointer, 2) an const char type indicating the value to search. 
 **/
bool node_search(node *head, const char *val);

/***
 * Function prepends entry onto a singly linked list. Function accepts two 
 * arguments: 1) a pointer type node to root pointer, 2) a char type indicating
 * the new data to be inserted into the new node.
 **/
void node_prepend(node **head, char *val);

/***
 * Function frees the space allocated by a single linked list starting at head. 
 * Function accepts one argument: 1) a pointer type node to root pointer.
 **/
void node_free(node *head);

#endif
