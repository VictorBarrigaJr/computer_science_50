/**
 *CS50, CS50 Study, Conditions
 *kids
 *Victor Barriga
 *victorbarriga@live.com
 *Program prompts the user for to input number (guess number of children per family in US)
 *if correct let the user know, correct answer = 2
 */
 
 #include <cs50.h>
 #include <stdio.h>
 
 int main(void)
 {
    // collect user input
    printf("What is the average number of children per family in the US?");
    int n = GetInt();    
    // if user is correct
    if (n == 2)
        // tell them they are correct
        printf("That is correct!\n");
    // else
    else
        // tell them they are not correct
        printf("That is incorrect!\n");
 }
 
