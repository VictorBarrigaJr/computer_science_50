/***
 * CS50 Study, data structures, queuesKhash tables
 * enqueue_and_dequeue.c
 *
 * Victor Barriga
 * victorbarriga@live.com
 *
 * Implement enqueue and dequeue function for this queue
 * characters. 
 *
 * jharvard@run.cs50.net (~): ./a.out
 * Enqueueing 10 strings...done!
 * Making sure that the queue size is indeed 10...good!
 * Making sure that enqueue() now returns false...good!
 * Dequeueing everything...done!
 * Making sure that dequeue() returned values in FIFO order...good!
 * Making sure that the queue is now empty...good!
 * Making sure that dequeue() now returns NULL...good!
 * Making sure that the head wraps around appropriately...good!
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

// the capacity of the queue
#define CAPACITY 10

// a queue
typedef struct 
{
    // the index of the first element in the queue
    int head;
    
    // storage for the elements in the queue
    char *strings[CAPACITY];
    
    //the size of the queue
    int size;
} queue;

// declare a queue (as a global variable)
queue q;

bool enqueue(char *str);
char *dequeue(void);

/***
 * Implement some simple test code for our queue
 **/
int main(int argc, char *argv[])
{
    // initialize the queue
    q.head = 0;
    q.size = 0;
    
    printf("Enqueueing %i strings...", CAPACITY);
    for (int i = 0; i < CAPACITY; i++) 
    {
        char str[12];
        sprintf(str, "%i", i);
        enqueue(strdup(str));
    }
    printf("done!\n");

    printf("Making sure that the queue size is indeed %i...", CAPACITY);
    assert(q.size == CAPACITY);
    printf("good!\n");

    printf("Making sure that enqueue() now returns false...");
    assert(!enqueue("too much!"));
    printf("good!\n");

    printf("Dequeueing everything...");
    char *str_array[CAPACITY];
    for (int i = 0; i < CAPACITY; i++) 
    {
        str_array[i] = dequeue();
    }
    printf("done!/n");

    printf("Making sure that dequue() returned values in FIFO order...");
    for (int i = 0; i < CAPACITY; i++) 
    {
        char str[12];
        sprintf(str, "%i", i);
        assert(strcmp(str_array[i], str) == 0);
        free(str_array[i]);
    }
    printf("good!\n");

    printf("Making sure that the queue is now empty...");
    assert(q.size == 0);
    printf("good!\n");

    printf("Making sure that dequeue() now returns NULL...");
    assert(dequeue() == NULL);
    printf("good!\n");

    printf("Making sure that the head wraps around appropriately...");
    for (int i = 0; i < CAPACITY; i++) 
    {
        assert(enqueue("cs50!"));
    }

    /***
     * to make sure that they adjust the head pointer appropriately, we'll 
     * enqueue and dequue a bunch of times to make sure they don't just walk off
     * the end of the char *strings[] array.
     **/
    for (int i = 0; i < CAPACITY * 10; i++) 
    {
        for (int j = 0; j < CAPACITY / 2; j++) 
        {
            assert(dequeue());
        }
        for (int j = 0; j < CAPACITY / 2; j++) 
        {
            assert(enqueue("cs50!"));
        }
    }
    printf("good!\n");
    
    printf("\n********\nSuccess!\n********\n");
    return 0;
}

/***
 * Puts a new element into the queue into the "end" of the data structure so 
 * that it will be retrived after the other elements already in the queue.
 **/
bool enqueue(char *str)
{
    // check if size is less than CAPACITY
    if(q.size == CAPACITY)
    {
        return false;
    }
    else
    {
        // store element at tail
        q.strings[(q.head + q.size) % CAPACITY] = str;

        // increment size
        q.size++;
        return true;
    }
}
/***
 * Retrieves ("dequeues") the first element in the queue, following the 
 * "first-in, first-out" (FIFO) ordering of the data structure. Reduces the 
 * size of the queue and adjusts the head to the next element.
 **/
char *dequeue(void)
{
    // check if there are elements to dequeue
    if(q.size == 0)
    {
        return NULL;
    }
    else
    {
        // store first element
        int to_output = q.head;
        
        // reposition head
        q.head = (q.head + 1) % CAPACITY;

        // decrement size
        q.size--;

        // return element at original head
        return(q.strings[to_output]);
    }
}
