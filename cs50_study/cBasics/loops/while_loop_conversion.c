/**
 *CS50, CS50 Study, Loops
 *while_loop_conversion
 *Victor Barriga
 *victorbarriga@live.com
 *Rewrite the folloing while loop as a do while loop:
 *int n = 0;
 *while (n<= 0)
 *{
 *  printf("Please enter a positive integer: ");
 *  n = GetInt();
 *}
 */
 
 #include <cs50.h>
 #include <stdio.h>

int main(int argc, string argv[])
{
    int n;

    do 
    {
        // print instruction for userr
        printf("Enter a positive integer: ");
        // get int from user
        n = GetInt();
    }
    // while n is not positive
    while (n < 1);
}
