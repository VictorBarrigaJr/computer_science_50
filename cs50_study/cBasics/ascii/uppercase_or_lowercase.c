/**
 *CS50 Study, C Basics, ASCII
 *uppercase_or_lowercase.c
 *Victor Barriga
 *victorbarriga@live.com
 *program prompts the user to enter an alphabetical character
 *program determines whether the character is uppercase or lowercase
*/

#include <cs50.h>
#include <stdio.h>

int main (int argc, string argv[])
{
    // Collect user input
    printf("Please enter an alphabetical character: ");
    char c = GetChar();
    
    // If letter is upercase
    if (c >= 'A' && c <= 'Z')
        printf("Thank you for the uppercase letter!\n");
    
    // If letter is lowercase
    else if (c >= 'a' && c <= 'z')
        printf("Thank you for the lowercase letter!\n");
    
    // If not an alphabetical character
    else
        printf("You did not enter an alphabetical character!\n");
}
