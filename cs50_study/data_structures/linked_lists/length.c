/***
 * CS50 Study, data structures, linked lists
 * length.c
 *
 * Victor Barriga
 * victorbarriga@live.com
 * 
 * function returns the length of a singly linked list
 *
 **/

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct node
{
    // the value to stroe in this node
    int n;
    // the link to the next node in the list
    struct node *next;
} node;

node *head = NULL;

int length(void);

int main(int argc, char *argv[])
{
    int i;
    // create linked list
    for (i = 0; i < SIZE; i++) 
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

    printf("Making sure that list length is indeed %i...\n", SIZE);

    // test length function
    assert(length() == SIZE);
    printf("good!\n");
    
    return 0;
}

int length(void)
{
    int length = 0;
    node *ptr;
    // traverse list
    for (ptr = head; ptr!= NULL; ptr = ptr->next) 
    {
        // count nodes
        length++;
    }

    // return length
    return length;
}
