/**
 *CS50, CS50 Study, Maths
 *percentages
 *Victor Barriga
 *victorbarriga@live.com
 *Program prompts the user for non-negative numerator and positive denominator 
 *Prints the fraction as a percent up to 2 decimal spaces
*/

#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    int numerator = 0;
    // ask user for numerator
    do 
    {
        printf("Please enter a non-negative numerator: ");
        numerator = GetInt();
    }
    while (numerator < 0);
    
    int denominator = 0;
    // ask user for denominator
    do 
    {
        printf("Please enter a positive denominator: ");
        denominator = GetInt();
    }
    while (denominator <= 0);
     
    // convert fraction to percent
    float percent = ((float) numerator / denominator) * 100;
    
    // display result
    printf("%.2f\n", percent);

}
