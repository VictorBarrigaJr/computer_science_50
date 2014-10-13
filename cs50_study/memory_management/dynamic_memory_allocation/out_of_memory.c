/**
 * CS50 Study, memory management, dynamic memory allocation
 * out_of_memory.c
 *
 * Victor Barriga
 * victorbarriga@live.com
 * 
 * program that coninuously mallocs a single byte until malloc(1) fails.
 * print out how many times malloc(1) was successful.
 *
 */
 
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    char* ptr;
    int counter = 0;
    // call malloc(1) until it return NULL
    while (malloc(1) != NULL)
    {
        // keep track of the number of times malloc(1) executes
        counter++;
    }    
    // print the nubmer of times malloc(1) successfully executed
    printf("%i\n", counter);
}
