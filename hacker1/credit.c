/***
 * credit.c (c) by Victor Barriga
 * 
 * credit.c is licensed under a
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 * 
 * You should have received a copy of the license along with this
 * work.  If not, see <http://creativecommons.org/licenses/by-nc-sa/3.0/>.
 * 
 * credit.c 
 * Computer Science 50
 * Problem Set 1 - Hacker 1 
 * 
 * Usage: ./credit
 *
 * Proram receives input from the user by asking for a credit card number.
 * The program returns whether the card is a valid AMEX, MC, VS, or invalid.
 **/
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <cs50.h>

int card_type(char cc_num[], int cc_len);
int luhn(char cc_num[], int cc_len);

int main (void)
{
    long long int temp_cc_num;
    char cc_num[16]; 
    int cc_len, cc_type;
  
    // prompt user for input (credit card number).
    printf("Please provide a valid credit card number\n"
           "(AMEX 16 digits, MC 15 digits or VISA 13 or 16 digits): \n");
        temp_cc_num = GetLongLong();
        //scanf("%lli", &temp_cc_num);
        
    // check if number is negative, return 1, INVALID
    if ( temp_cc_num < 0 )
    {
        printf("\nUsage: ./credit <credit card number>\n");
        return 1;
    }
    
    // copy user input integer into a string.
    sprintf(cc_num, "%lli", temp_cc_num);
    cc_len = strlen(cc_num); 
    cc_type = card_type(cc_num, cc_len);
    
    // run luhn test and card type check, print result.
    if ( luhn(cc_num, cc_len) != 0 && cc_type > 1 )
    {        
        if ( cc_type == 4 )
            printf("AMEX\n");
        else if ( cc_type == 3 )
            printf("MASTERCARD\n");
        else
            printf("VISA\n"); 
    }
    else
        printf ("INVALID\n");  
        
    return 0; 
}
/**
 * Function to determine card type.
 */
int card_type(char cc_num[], int cc_len)
{
    if ( cc_len == 15 && cc_num[0] == '3' && 
       ( cc_num[1] == '4' || cc_num[1] == '7' ) ) 
        return 4;   
    else if ( cc_len == 16 && cc_num[0] == '5' &&     
            ( cc_num[1] >= '1' || cc_num[1] <= '5' ) )
        return 3;
    else if ( ( cc_len == 13 || cc_len == 16 ) 
            && cc_num[0] == '4' )
        return 2;
    else
        return 1; 
}
/**
 * luhn test function
 */
int luhn(char cc_num[], int cc_len)
{   
    const int digits[] = {0, 2, 4, 6, 8, 1, 3, 5, 7, 9};
    int i, odd = 1, sum = 0;
    
    for ( i = cc_len; i--; odd = !odd ) 
    {
        int digit = cc_num[i] - '0';
        sum += odd ? digit : digits[digit];
    }    
    return sum % 10 == 0;
}

/*******************************************************************************
jharvard@appliance (~/Dropbox/cs50/week1/hacker1): make credit
clang -ggdb3 -O0 -std=c99 -Wall -Werror    credit.c  -lcs50 -lm -o credit

jharvard@appliance (~/Dropbox/cs50/week1/hacker1): check50 2014/x/hacker1/credit
credit.c
:) credit.c exists
:) credit.c compiles
:) identifies 378282246310005 as AMEX
:) identifies 371449635398431 as AMEX
:) identifies 5555555555554444 as MASTERCARD
:) identifies 5105105105105100 as MASTERCARD
:) identifies 4111111111111111 as VISA
:) identifies 4012888888881881 as VISA
:) identifies 1234567890 as INVALID
:) rejects a non-numeric input of "foo"
:) rejects a non-numeric input of ""
*******************************************************************************/
