/**
 *CS50, CS50 Study, Loops
 *square
 *Victor Barriga
 *victorbarriga@live.com
 * Take as input a non-negative integer, n, no larger than 23.  
 * Use nested loops to pring an n-by-n square using (#) at the command line.
 * Give ma a number between 1 and 23: 3
 * ###
 * ###
 * ###
 */
 
 #include <cs50.h>
 #include <stdio.h>

int main(int argc, string argv[])
{
    int n;
    // get dimension from user
    do
    {
        printf("Give me a number between 1 and 23: ");
        n = GetInt();
    }
    while (n < 1 || n > 23);
    
    // iterate accross height
    for (int i = 0; i < n; i++)
    {
        // iterate accross width
        for (int i =0; i < n; i++)
            
            // print the character #
            printf("#");
            
        // move on to the next line
        printf("\n");
    }
}
