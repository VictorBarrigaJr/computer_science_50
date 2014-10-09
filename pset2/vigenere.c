/*******************************************************************************
 * Assignment:   CS50, pset2,Parlez-vous fancais?
 * FILE:         vigenere.c
 * 
 * Author:       Victor Barriga
 * Email:        victorbarriga@live.com
 * 
 * The program demonstrates the use of a cryptography by implementing Vigenere's 
 * Cipher, which enctypts messages by rotating each letter by Kith positions, 
 * wrapping aroung from Z to A as needed. If p is some plaintext (unencrypted),
 * p is the ith character in p, and k is the keyword (non-negatice integer), 
 * then each letter, Cith, in the ciphertext, c, is computed as:
 *       Cith =( Pith + Kith ) % 26
 * For example if the key, k is 'bacon'13, and the plaintext, p is:
 *       "Meet me at the park at eleven am""
 * By encrypting that p with that keyword in order to get the ciphertext, c, by 
 * rotating each of the letter p by Kith places, becomes: 
 *       "Negh zf av huf pcfx bt gzrwep oz".
 * The program mut encrypt the message using Vigenere's cipher, and must accept
 * a single command-line argument: a keyword, k, composed of only alphabetical
 * characters. If the program is executed without a command line argument it
 * should return 1. Otherwise the program must proceed to prompt the user for a
 * string of paintext, then output the text parsed through the cipher rotated by
 * Kith positions, non-alphabetical chars must passed unchanged, and it must
 * preserve capitalization.
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cs50.h>

/**
 * Function prototypes
 */
bool is_alphabetical (char string[]);
int string_length (char string[]);
void copy_and_paste (char copy[], char paste[]);
void read_line (char buffer[]);
int get_key (char k);
char character_case (char c, int key);
void vigenere (char string[], char keyword[]);

int main (int argc, char *argv[])
{
    char text[300]; // String array to store user input text.
    
    /* verify contents of command-line arg, keyword, composed entirely of
       alphabetical characters, and is not empty, or more than one arg. */
    if ( argc != 2 || ! is_alphabetical ( argv[1]) )
    {
        printf ("Input: ./vigenere <keyword>. Where keyword is a-z A-Z.\n");
        return 1;
    }
    
    char keyword[string_length (argv[1])];  // Assign array to hold keyword
    
    copy_and_paste (argv[1], keyword);
    read_line(text);                        // Get input string from user
    vigenere (text, keyword);               // encrypt the users input 
    printf ("%s\n", text);    
}

/******************************************************************************/
/**
 * Function to verify if arg[] is alphabetical, returns bool.
 */
bool is_alphabetical (char string[])
{   
    bool is_alpha_flag = false;
    for ( int i = 0; string[i] != '\0'; ++i )
    {
        if ( ( string[i] >= 'a' && string[i] <= 'z' ) || 
             ( string[i] >= 'A' && string[i] <= 'Z' ) )
            is_alpha_flag = true;
        else
            return is_alpha_flag = false;            
    }
    
    return is_alpha_flag;
}
/**
 * Function to count the number of elements in a given array.
 */
int string_length (char string[])
{
    int count = 0;
    
    while ( string[count] != '\0' )
        ++count;
    return count;
}
/**
 * Function to copy and paste elements of an array into another array. 
 */
void copy_and_paste (char copy[], char paste[])
{
    int i;
    for ( i = 0; i < string_length (copy); ++i )
        paste[i] = copy[i];
    paste[i] = '\0';
}
/**
 * Function to receive plain text from the user and assigns each char into the
 * argument array.
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
    while ( character != '\n' );
    
    buffer[i -1] = '\0';
}
/**
 * Function to get key based on each char of the keyword.
 */
int get_key (char k)
{
    if ( k >= 'a' && k <= 'z' )
        return k - 'a';    
    
    else if ( k >= 'A' && k <= 'Z')
        return k - 'A';
    else
        return 0; 
}
/**
 * Function to test character caase and switch tto appropriate case based on key
 */
char character_case (char c, int key)
{   
    if ( c >= 'a' && c <= 'z' )
    {
        c -= 'a';
        c = (c + key) % 26;        
        return c += 'a';    
    }
    else if ( c >= 'A' && c <= 'Z')
    {
        c -= 'A';
        c = (c + key) % 26;
        return c += 'A';
    }
    else
        return c;
}
/**
 * Function to iterate through text & rotate letters by key
 */
void vigenere (char string[], char keyword[])
{
    char keyword_string[string_length (string)];
    int key, j = 0;
    
    for ( int i = 0; string[i] != '\0'; ++i )
    {           
        if ( keyword[j] == '\0' )
            j = 0;
           
        if ( ( string[i] >= 'a' && string[i] <= 'z' ) ||
             ( string[i] >= 'A' && string[i] <= 'Z' ) )
        {
            keyword_string[i] = keyword[j];
            key = get_key (keyword_string[i]);
            string[i] = character_case (string[i], key);
            j++;
        } 
        else
            keyword_string[i] = string[i];        
    }
    
    keyword_string[string_length (string)] = '\0';
}

/*******************************************************************************

(~/Dropbox/cs50/week2/pset2): make vigenere
clang -ggdb3 -O0 -std=c99 -Wall -Werror    vigenere.c  -lcs50 -lm -o vigenere

(~/Dropbox/cs50/week2/pset2): check50 2014/x/pset2/vigenere vigenere.c
:) vigenere.c exists
:) vigenere.c compiles
:) encrypts "a" as "a" using "a" as keyword
:) encrypts "world, say hello!" as "xoqmd, rby gflkp!" using "baz" as keyword
:) encrypts "BaRFoo" as "CaQGon" using "BaZ" as keyword
:) encrypts "BARFOO" as "CAQGON" using "BAZ" as keyword
:) handles lack of argv[1]
:) handles argc > 2
:) rejects "Hax0r2" as keyword
https://sandbox.cs50.net/checks/71d267240d4b42d6822ebc395262a1b4

*******************************************************************************/
