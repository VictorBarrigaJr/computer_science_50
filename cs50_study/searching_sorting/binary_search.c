/**
 * CS50 Study, C Basics, searching and sorting
 * binary_search.c
 *
 * Victor Barriga
 * victorbarriga@live.com
 * 
 * uses binary search to determine whether needle is in haystack.
 * returns true if needle is found false otherwise.
 *
 */
 
 #include <stdio.h>
 #include <cs50.h>
 
 #define SIZE 8
 
 bool search(int needle, int haystack[], int size);
 
 int main(void)
 {
    int numbers[SIZE] = { 4, 8, 15, 16, 23, 42, 50, 108 };
    printf("> ");
    int n = GetInt();
    if (search(n, numbers, SIZE))
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }
 }
 
 bool search(int needle, int haystack[], int size)
 {
    // assign beginning, end and middle variables of search area
    int beginning = 0, end = size - 1;
    

    while (beginning <= end)
    {
        int middle = (beginning + end) / 2;
        if (haystack[middle] == needle)
        {
            return true;
        }
        // needle is less than middle
        else if (haystack[middle] > needle)
        {
            // reset array search area
            end = middle - 1;        
        } 
        // needle is greater than middle
        else if (haystack[middle] < needle)
        {
            // reset array search area
            beginning = middle + 1;
        }
    }
    return false;
 }
