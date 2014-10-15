/***
 * CS50 Study, data structures, linked lists
 * contains.c
 *
 * Victor Barriga
 * victorbarriga@live.com
 *
 * function that returns true if a node in the linked list contains int i and
 * false otherwise.
 *
 **/

#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

typedef struct node
{
    // the value to store in this node
    int n;
    // the link to the next node in the list
    struct node *next;
} node;

node *head = NULL;

bool contains(int i);

int main(int argc, char *argv[])
{
    // create linked list
    int i;
    for (i = SIZE; i > 0; i--)
    {
        node *new = malloc(sizeof(node));

        if (new == NULL)
        {
            exit(1);
        }
        new->n = i;
        new->next = head;
        head = new;
    }

    printf("What value are you looking for? ");
    int j = GetInt();
    
    if  (contains(j))
    {
        printf("Found it! The list contains ");
    }
    else
    {
        printf("Sorry, the list only contains ");
    }
    
    node *ptr;
    for (ptr = head; ptr != NULL; ptr = ptr->next) 
    {
        printf("%i  ", ptr->n);
    }
    printf("\n");

    return 0;
}

bool contains(int j)
{
    // traverse list
    node *ptr;
    for (ptr = head; ptr != NULL; ptr = ptr->next) 
    {
        // check each node
        if (ptr->n == j)
        {
            // return true we find value
            return true;
        }
    }
    // return false if we haven't found value
    return false;
}
