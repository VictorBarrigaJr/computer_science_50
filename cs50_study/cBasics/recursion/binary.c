/**
 * CS50 Study, C Basics, recursion
 * binary.c
 *
 * Victor Barriga
 * victorbarriga@live.com
 * 
 * a recursive binary search function  
 *
 */
 
#include <stdio.h>
#include <cs50.h>

#define SIZE 8

bool search(int n, int array[], int lower, int upper);
 
int main(void)
{
    int numbers[SIZE] = { 4, 8, 15, 16, 23, 42, 50, 108 };
    printf("> ");
    int n = GetInt();
    if (search(n, numbers, 0, SIZE - 1))
    {
        printf("Yes\n");
    }
    else
    {
        printf("No\n");
    }
 
}
 
bool search(int n, int array[], int lower, int upper)
{
    // if n is not in array
    if (upper < lower)
    {
        return false;
    }
    else
    {
        // assign middle
        int middle = (lower + upper) / 2;
        
        // test if n is <, > middle.
        if (array[middle] > n)
        {
            // less than half of array
            return search(n, array, lower, middle - 1);
        }
        else if (array[middle] < n)
        {
            // greater than half of array
            return search(n, array, middle + 1, upper);
        }
        else
        {   
            // n found at middle
            return true;
        }
    } 
}
 
 
 
