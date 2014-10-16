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
 * jharvard@run.cs50.net (~): ./a.out
 * Pushing 10 strings onto the stack...
 * 0
 * 1
 * 2
 * 3
 * 4
 * 5
 * 6
 * 7
 * 8
 * 9
 * done!
 * Making sure that the stack size is indeed 10...good!
 * Making sure that push() now returns false...good!
 * 
 * ********
 * Success!
 * ********
 **/

// for strdup() in the testing code
#define _XOPEN_SOURCE 500

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// the capacity of the stack
#define CAPACITY 10

typedef struct
{
    // storage for the elements in the stack
    char *strings[CAPACITY];

    // the number of elements currently in the stack
    int size;
} stack;

// declare a stack (as a global variable)
stack s;

bool push(char *str);

/***
 * Implements some simple test code for our stack
 **/
int main(void)
{
    // initialize the stack
    s.size = 0;

    printf("pushing %i strings onto the stack...\n", CAPACITY);
    int i;
    for (i = 0; i < CAPACITY; i++) 
    {
        char str[12];
        sprintf(str, "%i", i);
        push(strdup(str));
        printf("%s\n", str);
    }
    printf("done!\n");

    printf("Making sure that the stack size is indeed %i...", CAPACITY);
    assert(s.size == CAPACITY);
    printf("good!\n");

    printf("Making sure that push() now returns false...");
    assert(!push("too much!"));
    printf("good!\n");

    printf("\n********\nSuccess\n********\n");

    return 0;
}

/***
 * Puts a new element into the stack onto the "top" of the data structure so 
 * that it will be retrived prior to the elements already in the stack.
 **/
bool push(char *str)
{
    // check if stack is at CAPACITY
    if(s.size == CAPACITY)
    {
        return false;
    }
    else
    {
        // store element at tail
        s.strings[s.size] = str;

        // increment size
        s.size++;
        return true;
    }
}
