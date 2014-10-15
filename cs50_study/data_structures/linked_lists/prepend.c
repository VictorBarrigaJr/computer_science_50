/***
 * CS50 Study, data structures, linked lists
 * prepend.c
 *
 * Victor Barriga
 * victorbarriga@live.com
 * 
 * function that prepends a new node containing <tt>int i</tt> to the front fo 
 * a singly linked list
 *
 **/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct node
{
    // the value to store in this node
    int n;
    // the link to the next node in the list
    struct node *next;
}node;

node *head = NULL;

void prepend(int i);

int main(int argc, char *argv[])
{
    // creating list
    printf("Prepending ints 0-%i onto the list... ", SIZE - 1);
    int i;
    for (i = 0; i < SIZE; i++) 
    {
        prepend(i);
    }
    printf("done!\n");

    // printing out list
    printf("Your list contains ");
    node *ptr;
    for (ptr = head; ptr != NULL; ptr = ptr->next) 
    {
        printf("%i ", ptr->n);
    }
    printf("\n");

    return 0;
}

void prepend(int i)
{
    // build new node
    node *new = malloc(sizeof(node));

    if (new == NULL)
    {
        exit(1);
    }
    // initialize new node
    new->n = i;

    // add new node to head of list
    new->next = head;
    head = new;
}
