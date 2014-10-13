/**
 *CS50, CS50 Study, Loops
 *for_loop_conversion
 *Victor Barriga
 *victorbarriga@live.com
 *Rewrite the following loop into a single loop, with the same output.
 *for (int i = 0; i < 5; i++)
 *  for (int j = 0; j < 5: j++);
 *      printf("i = %d, j = %d\n", i, j);
 */
 
 #include <cs50.h>
 #include <stdio.h>

int main(int argc, string argv[])
{
    // iterate from 0 through 25
    for (int i = 0; i < 25; i++)
        
        // use division and mod to print combos of numbers
        printf("i = %i, j = %i\n", i / 5, i % 5);

}
