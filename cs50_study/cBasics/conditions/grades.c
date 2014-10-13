/**
 *CS50, CS50 Study, Conditions
 *grades
 *Victor Barriga
 *victorbarriga@live.com
 *Fix the bugProgram prompts the user for to input number (95)
 *the correct string prints out
 * enter valid grade: 95 ---> You got an A!
 */
 
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    
    do
    {
        printf("Enter a valid grade: ");
        n = GetInt();
    }
    while (n > 100 || n < 60);
    
    // TODO: fix the bug!
    if (n >= 90)
        printf("You got an A!\n");
    else if (n >= 80)
        printf("You got a B!\n");
    else if (n >= 70)
        printf("You got a C!\n");
    else printf("You got a D!\n");
}
