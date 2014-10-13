/**
 * CS50 Study, memory management, pointers
 * swap.c
 *
 * Victor Barriga
 * victorbarriga@live.com
 * 
 * initiates a swap function that swaps the values with ponters
 *
 */
 
 #include <stdio.h>
 #include <cs50.h>
 
 void swap(int* a, int* b);
 
 int main(void)
 {
    int x = 1;
    int y = 2;
    
    printf("x is %i\n", x);
    printf("y is %i\n", y);
    printf("Swapping...\n");
    swap(&x, &y);
    printf("Swapped!\n");
    printf("x is %i\n", x);
    printf("y is %i\n", y);
 }
 
 void swap(int*a, int* b)
 {
    // store *a in tmp
    int tmp = *a;
    // assign *a to  *b
    *a = *b;
    // assign tmp to *b
    *b = tmp;
 }
