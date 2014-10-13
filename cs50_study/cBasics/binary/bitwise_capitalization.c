/**
 *CS50, CS50 Study, Binary
 *bitwise_capitalization
 *Victor Barriga
 *victorbarriga@live.com
 *Program prompta the user to enter a lowercase letter, must be lowercase letter
 *utilize bitwise operators to capitalize the letter
 */
 
 #include <cs50.h>
 #include <stdio.h>
 
 int main(int argc, string argv[])
 {
    char lower;
    
    // collect user input
    do
    {
        printf("Please input a lowercase letter: ");
            lower = GetChar();
    }
    while (lower < 'a' || lower > 'z');
    
    // capitalize by &-ing with 11011111 or 223
    char upper = lower & 223;
    
    // print capitalized letter
    printf("%c\n", upper);
 }
 
 
