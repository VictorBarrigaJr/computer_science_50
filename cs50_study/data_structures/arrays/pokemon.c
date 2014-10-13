/**
 * CS50 Study, data structures
 * pokemon.c
 *
 * Victor Barriga
 * victorbarriga@live.com
 * 
 * uses insertion sort to sort the array.
 *
 */
 
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
#define MAX 5
 
int main (int argc, string argv[])
{
    // declare array storage for Pokemon
    string pokeballs[MAX];
    // collect and store Pokemon
    for (int i = 0; i < MAX; i++)
    {
        printf("Give me a Pokemon: ");
        string pokemon = GetString();
        pokeballs[i] = pokemon;
    }
    // initialize random seed
    srand(time(NULL));
    
    // chose and print out random Pokemon
    printf("%s, I choose you!\n", pokeballs[rand() % 5]);
    
    return 0;
}
