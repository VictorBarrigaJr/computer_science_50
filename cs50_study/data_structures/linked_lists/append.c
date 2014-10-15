/***
 * CS50 Study, data structures, linked lists
 * append.c
 *
 * Victor Barriga
 * victorbarriga@live.com
 *
 * function that appends a new node containing int i at the end of a singly 
 * linked list.
 *
 **/
 
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct node
{
    // the value to store in this node
    int n;
    // the link to the next node in the list
    struct node *next;
} node;

node *head = NULL;

void append(int i);

int main(int argc, char *argv[])
{
    // creating list
    printf("Appending ints 0-%i onto the list...\n", SIZE - 1);
    int i;
    for (i = 0; i < SIZE; i++) 
    {
        append(i);
    }
    printf("done!\n");

    //printing out list
    printf("Your list contains ");
    node *ptr;
    for (ptr = head; ptr != NULL; ptr = ptr->next) 
    {
        printf("%i ", ptr->n);
    }
    printf("\n");

    return 0;
}


void append(int i)
{
    // build new node
    node *new = malloc(sizeof(node));
    
    if (new == NULL)
    {
        exit(1);
    }
    
    // initialize new node
    new->n = i;
    new->next = NULL;
    
    // traverse list with two pointers
    node *prev = NULL;
    node *cur;
    for (cur = head; cur != NULL; cur = cur->next) 
    {
        prev = cur;
    }

    // if the list is empty, prepend
    if (prev == NULL)
    {
        head = new;
    }
    // else add new node to end of the list
    else
    {
        prev->next = new;
    }
        
}
