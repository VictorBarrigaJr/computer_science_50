/**
 * CS50 Study, C Basics, searching and sorting
 * bubble_sort.c
 *
 * Victor Barriga
 * victorbarriga@live.com
 * 
 * uses bubble sort to sort the array.
 *
 */
 
#include <stdio.h>
#include <cs50.h>

#define SIZE 8  

void bubble_sort(int array[], int size);
 
int main(void)
{
    int numbers[SIZE] = { 4, 15, 16, 50, 8, 23, 42, 108 };
    
    for (int i = 0; i < SIZE; i++)
    {
        printf("%i ", numbers[i]);
    } 
    printf("\n");
    
    bubble_sort(numbers, SIZE);
    
    for (int i = 0; i < SIZE; i++)
    {
        printf("%i ", numbers[i]);
    } 
    printf("\n");
}

void bubble_sort(int array[], int size)
{
    int swaps;
    
    do
    {
        // reset swaps to 0
        swaps = 0;
        // iterate through entire aray
        for (int i = 0; i < size - 1; i++)
        {
            if (array[i] > array[i + 1])
            {
                // swap
                int temp     = array[i];
                array[i]     = array[i + 1];
                array[i + 1] = temp;
                // increment swaps
                swaps++;
            }
        }
        
    }
    while(swaps != 0);
}
