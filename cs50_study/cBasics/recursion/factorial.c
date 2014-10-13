/**
 * CS50 Study, C Basics, recursion
 * factorial.c
 *
 * Victor Barriga
 * victorbarriga@live.com
 * 
 *
 */

#include <stdio.h>

int factorial(int n);

int main (void)
{
    printf("%i\n",factorial(6));
}
/**
 * factorial
 */
int factorial(int n)
{
    // base case
    if ( n < 2 )
    {
        return 1;
    }
    
    // recursive case
    return n * factorial( n - 1 );
}

