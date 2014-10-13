/**
 *Cs50, CS50 Study, Binary
 *decimal_to_binary
 *Victor Barriga
 *victorbarriga@live.com
 *The program takes a positive decimal value as iinput
 *it then prints out that number in binary notation
*/

#include <cs50.h>
#include <stdio.h>

int main (int argc, string argv[])
{
    int n;
    
    // collect user input
    do
    {
        printf("Please enter a positive decimal value: ");
        n = GetInt();
    }
    while (n <= 0);
    
    // create array to store binary digits
    int binary[31];
    
    // keep track of position in binary array
    int digit;
     
    // calculate binary digits by repeatedly dividing by 2
    for (digit = 0; n != 0; digit++, n /= 2)    
        //store binary digits in array
        binary[digit] = n % 2;
    
    //print out binary array
    for (digit = digit -1; digit >= 0; digit--)
        printf("%i", binary[digit]);
        
    printf("\n");
    return 0;
}
