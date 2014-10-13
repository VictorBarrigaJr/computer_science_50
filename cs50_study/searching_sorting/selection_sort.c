/**
 * CS50 Study, C Basics, searching and sorting
 * selection_sort.c
 *
 * Victor Barriga
 * victorbarriga@live.com
 * 
 * uses selection sort to sort the array.
 *
 */
 
#include <stdio.h>
#include <cs50.h>

#define SIZE 8  

void selection_sort(int array[], int size);
 
int main(void)
{
    int numbers[SIZE] = { 4, 15, 16, 50, 8, 23, 42, 108 };
    
    for (int i = 0; i < SIZE; i++)
    {
        printf("%i ", numbers[i]);
    } 
    printf("\n");
    
    selection_sort(numbers, SIZE);
    
    for (int i = 0; i < SIZE; i++)
    {
        printf("%i ", numbers[i]);
    } 
    printf("\n");
}
void selection_sort(int array[], int size)
{
    // for i = 1 to size -1
    for (int i = 0; i < (size - 1); i++)
    {
        // smallest value set to i
        int smallest_index = i;
        
        // compare smallest_index to all ogher elements in unsorted subarray
        for (int j = (i + 1); j < size; j++)
        {
            // if you find a smaller element, that is now smallest_index
            if (array[j] < array[smallest_index])
            {
                smallest_index = j;
            }
        }
        
        // swap to put the smallest_index in correct position
        int tmp = array[smallest_index];
        array[smallest_index] = array[i];
        array[i] = tmp;
    }
}
