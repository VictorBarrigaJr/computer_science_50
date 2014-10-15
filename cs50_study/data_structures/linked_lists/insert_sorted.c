/***
 * CS50 Study, data structures, linked lists
 * insert_sorted.c
 *
 * Victor Barriga
 * victorbarriga@live.com
 *
 * function that inserts a new node containing int i into the appropriate 
 * position in a list of sorted in ascending order.
 *
 **/

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

void insert_sorted(int i);

int main(int argc, char *argv[])
{
    printf("Inserting %i random ints to the list...\n", SIZE);
    int i;
    for (i = 0; i < SIZE; i++) 
    {
        insert_sorted(rand() % SIZE);
    }
    printf("done!\n");

    //printing out list
    printf("Your list now contains ");
    node *ptr;
    for (ptr = head; ptr != NULL; ptr = ptr->next) 
    {
        printf("%i ", ptr->n);
    }
    printf("\n");
    
    return 0;
}


void insert_sorted(int i)
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
        //break if we wing a value larger than i
        if (cur->n > i)
        {
            break;
        }
        else
        {
            prev = cur;
        }
    }

    // if new belongs at head, prepend
    if (prev == NULL)
    {
        new->next = head;
        head = new;
    }
    // else insert in middle or end
    else
    {
        new->next = prev->next;
        prev->next = new;
    }    
}
