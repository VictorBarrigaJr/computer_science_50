/**
 * CS50 Study, C Basics, recursion
 * sigma.c
 *
 * Victor Barriga
 * victorbarriga@live.com
 * 
 *
 */
 
#include <stdio.h>
#include <cs50.h>

int sigma(int n);

int main(void)
{
    int n;
    do 
    {
    printf("Enter a positive interger: ");
        n = GetInt(); 
    }
    while (n < 1);
        
    printf("%i\n", sigma(n));
    
    return 0;
}

int sigma(int n)
{
    if (n <= 0)
    {
        return 0;
    }
    else
    {
        return (n + sigma(n - 1));
    }   
}
