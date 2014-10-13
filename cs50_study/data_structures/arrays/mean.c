/**
 * CS50 Study, data structures
 * mean.c
 *
 * Victor Barriga
 * victorbarriga@live.com
 *
 */
 
#include <cs50.h>
#include <stdio.h>

#define N 5

int main(void)
{
    // array storage for ints
    int values[N];
    
    // collect and store ints
    for (int i = 0; i < N; i++)
    {
        printf("Give me an integer: ");
        int value = GetInt();
        values[i] = value;
    }
    //calculate mean
    int sum = 0;
    for (int i = 0; i < N; i++)
    {
        sum += values[i];
    }   
    float mean = (float)sum / (float)N;
    
    // print mean
    printf("Mean: %.2f\n", mean);  
}
