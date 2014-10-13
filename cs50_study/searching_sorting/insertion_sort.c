/**
 * CS50 Study, C Basics, searching and sorting
 * insertion_sort.c
 *
 * Victor Barriga
 * victorbarriga@live.com
 * 
 * uses insertion sort to sort the array.
 *
 */
 
#include <stdio.h>
#include <cs50.h>

#define SIZE 8  

void insertion_sort(int array[], int size);
 
int main(void)
{
    int numbers[SIZE] = { 4, 15, 16, 50, 8, 23, 42, 108 };
    
    for (int i = 0; i < SIZE; i++)
    {
        printf("%i ", numbers[i]);
    } 
    printf("\n");
    
    insertion_sort(numbers, SIZE);
    
    for (int i = 0; i < SIZE; i++)
    {
        printf("%i ", numbers[i]);
    } 
    printf("\n");
}

void insertion_sort(int array[], int size)
{
    // iterate through unsorted part of array 
    for(int i = 1; i < size; i++)
    {
        // define the start of the sorted array
        int j = i - 1;
        // define next element to sorted
        int to_sort = array[i];
            
        // iterate through sorted part of array 
        // figure out where in sorted portion elemnt should go
        while (j >= 0 && to_sort < array[j])
        {          
            // shift sorted elements rightward
            array[j + 1] = array[j];
            j--; 
        }
            
        // insert element into sorted portion of array
        array[j + 1] = to_sort;
    }
}
