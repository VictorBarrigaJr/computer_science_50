/***
 * caesar.c (c) by Victor Barriga
 * 
 * caesar.c is licensed under a
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 * 
 * You should have received a copy of the license along with this
 * work.  If not, see <http://creativecommons.org/licenses/by-nc-sa/3.0/>.
 * 
 * caesar.c 
 * Computer Science 50
 * Problem Set 2 
 * 
 * Usage: ./caesar <key>
 * 
 * The program demonstrates the use of a cryptography by implementing a Caesar 
 * Cipher, which enctypts messages by rotating each letter by k positions, 
 * wrapping aroung from Z to A as needed. If p is some plaintext (unencrypted), 
 * p is the ith character in p, and k is the key (non-negatice integer), then
 * each letter, Cith, in the ciphertext, c, is computed as:
 *       Cith =( Pith + k ) % 26
 * For example if the key, k is 13, and the plaintext, p is:
 *       "Be sure to drink your Ovaltine!"
 * By encrypting that p with that k in order to get the ciphertext, c, by 
 * rotating each of the letter p by 13 places, becomes: 
 *       "Or fher gb qevax lbhe Binygvar!".
 * The program mut encrypt the message using Caesar's cipher, and must accept a
 * single command-line argument: a non-negative integer, k. If the program is
 * executed without a command line argument it should return 1. Otherwise the
 * program must proceed to prompt the user for a string of paintext, then output
 * the text parsed through the cipher rotated by k positions, non-alphabetical
 * chars must passed unchanged, and it must preserve capitalization.
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cs50.h>

/**
 * Function prototyping
 */
bool is_int ( char string[] );
int str_to_int (char string[]);
void read_line (char buffer[]);
char rotate_character (char c, int key);
char character_case (char c, int key);
void caesar_cipher (char string[], int key);

int main (int argc, char *argv[])
{   
    char text[300]; // String array to hold input text from user

    // verify user input is a an int 'string' only 1 argument given & not zero  
    if ( argc != 2 || argv[2] != '\0' || ! is_int (argv[1]) )
    {
        printf ("\nPlease provide an apropriate key integer when executing.\n");
        return 1;
    }
     
    int key = str_to_int (argv[1]);     // convert input string 'key' to into
  
    read_line (text);                   // get input from user
    caesar_cipher (text, key);          // encrypt the input data from user
    
    printf ("%s\n", text);              // dislay encrypted text to console
    
    return 0;
}

/******************************************************************************/

/**
 * Function to test if input is an integer as a char, returns bool.
 */
bool is_int ( char string[] )
{
    if ( string[0] < '0' || string[0] > '9' )
       return false;
    else
       return true;
}
/**
 * Function to convert a string to an integer, by subtracting ascii int values.
 */
int str_to_int (char string[])
{
    int result = 0;
    
    for ( int i = 0; string[i] >= '0' && string[i] <= '9'; ++i )
    {
        int int_value = string[i] - '0';
        result = result * 10 + int_value;
    }
    
    return result;
}
/**
 * Function to receive plain text from the user assigns to string
 */
void read_line (char buffer[])
{
    char character;
    int i = 0;
    
    do
    {
        character = getchar ();
        buffer[i] = character;
        ++i;
    }
    while ( character != '\n');
    
    buffer[i -1] = '\0';
}
/*
 * Function to rotate characters by key if key reaches end roatate to 1
 */
char rotate_character (char c, int key)
{
   c = ((c + key) % 26);
   
   return c;
}
/*
 * Function to test character case and switch to appropriate case based on key
 */
char character_case (char c, int key)
{
    if ( c >= 'a' && c <= 'z' ) 
    {
        // lowercase 'a' 97
         c -= 'a';
         c = rotate_character (c, key);
         c += 'a';
         
         return c;
    }
    else if ( c >= 'A' && c <= 'Z' )
    {
        // uppercase 'A' 65
        c -= 'A';
        c = rotate_character (c, key);
        c += 'A';
       
        return c;
    }
    else // special characters
        return c;
}
/**
 *Function to iterate through text & rotate letters by key
 */
void caesar_cipher (char string[], int key)
{   
    for ( int i = 0; string[i] != '\0'; ++i )
    {
        string[i] = character_case (string[i], key);
    }
}
/*******************************************************************************

(~/Dropbox/cs50/week2/pset2): make caesar
clang -ggdb3 -O0 -std=c99 -Wall -Werror    caesar.c  -lcs50 -lm -o caesar

 (~/Dropbox/cs50/week2/pset2): check50 2014/x/pset2/caesar caesar.c
:) caesar.c exists
:) caesar.c compiles
:) encrypts "a" as "b" using 1 as key
:) encrypts "barfoo" as "yxocll" using 23 as key
:) encrypts "BARFOO" as "EDUIRR" using 3 as key
:) encrypts "BaRFoo" as "FeVJss" using 4 as key
:) encrypts "barfoo" as "onesbb" using 65 as key
:) encrypts "world, say hello!" as "iadxp, emk tqxxa!" using 12 as key
:) handles lack of argv[1]
https://sandbox.cs50.net/checks/a402606da93349b6aaaaaa8ac85f742d

*******************************************************************************/

