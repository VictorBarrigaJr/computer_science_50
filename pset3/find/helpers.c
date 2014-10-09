/***
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/** * Returns true if value is in array of n values, else false, binary search.
 */
bool search(int value, int values[], int n)
{
     // save bounds of list
    int beginning = 0;
    int end = n - 1;

    // while length of list > 0
    while (beginning <= end)
    {
        // look at middle of list
        int middle = (beginning + end) / 2;
        if (values[middle] == value)
        {
            // if number found, return true
            return true;
        }   
        
        // else if middle higher, search left
        else if (values[middle] > value)
        {
            end = middle - 1;
        }
        
        // else if middle lower, search right
        else
        {
            beginning = middle + 1;
        }
    }
    
    // return false
    return false;
}

/***
 * Sorts array of n values, using selection sort.
 */
void sort(int values[], int n)
{
     // run the sort n times
    for (int i = 0; i < n; i++)
    {
        // remember the smallest value
        int smallest_index = i;
        
        // make comparisons throughout the rest of the list
        for (int j = i + 1; j < n; j++)
        {
            // find the smallest number
            if (values[j] < values[smallest_index])
            {
                smallest_index = j;
            }
        }
        
        // put the beginning of the list where the smallest number was
        int tmp = values[smallest_index];
        values[smallest_index] = values[i];

        // place it in the beginning of the list
        values[i] = tmp;
    }
    return;
}
/*******************************************************************************
Check50 - search function 
(~/Dropbox/cs50/week3/pset3/find): check50 2014/x/pset3/find helpers.c
:) helpers.c exists
:) helpers.c compiles
:) finds 42 in {42,43,44}
:) finds 42 in {41,42,43}
:) finds 42 in {40,41,42}
:) finds 42 in {41,42,43,44}
:) finds 42 in {40,41,42,43}
:) finds 42 in {39,40,41,42}
:) doesn't find 42 in {39,40,41}
:) doesn't find 42 in {39,40,41,43}
https://sandbox.cs50.net/checks/4b3d1148be2d4a93b0ca72673c1eeafb

*******************************************************************************/

