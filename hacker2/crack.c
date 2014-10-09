/*******************************************************************************
 * crack.c (c) by Victor Barriga
 * 
 * crack.c is licensed under a
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 * 
 * You should have received a copy of the license along with this
 * work.  If not, see <http://creativecommons.org/licenses/by-nc-sa/3.0/>.
 * 
 * crack.c 
 * Computer Science 50
 * Problem Set 2 - Hacker 2
 *
 * Usage:       ./crack.3 <encrypted password (13 characters)> 
 *  
 * On most, systems running Linux or Unix is a file called /etc/passwd. By
 * design, this file is meant to contain usernames and passwords along with
 * other account-related details (e.g. paths to user directories and shells).
 * Also by poor design, this file is typically word-readable. The passwords are
 * not stored in the clear, but are encrypted using a "one-way has function."
 * When a user logs int the system by typing a username and password, the latter
 * is encrypted with the very same hash function, and the result is compared
 * against the username's entry in /etc/passwd. If the two ciphertexts match,
 * the user is allowed in.
 * 
 * Even though passwords in /etc/passwd are encrypted, the crypto involved is
 * not terribly strong. Once obtaining files like this one, one is able to guess
 * the user's password by useing brute force (i.e. trying all possible passwords
 * ). 
 *
 * The following are examples of some <username:ciphertext> pairs from a fake 
 * system: 
 *      caesar:50zPJlUFIYY0o
 *      hirschhorn:50q.zrL5e0Sak
 *      jharvard:50yoN9fp966dU
 *      malan:HA610l/.LeOak
 *      milo:HAL7ye0Ms7wZY
 *      zamyla:50NwUtF.OmQNY
 * The following program cracks the passwords, all of which has been encrypted 
 * with C's DES-based (notMD5-based) crypt function. The program accepts a
 * single command-line argument: an encrypted password. If the program is
 * executed with no command-line argument or more than one command-line
 * argument, the program displays an error message, immediately exits main, and
 * returns 1. The program then proceeds to crack the given password, as quickly
 * as possible, printing to standard output the password in the clear followed
 * by '\n', main then returns 0.
 *
 * The program behaves as follows:
 *      jharvard@appliance (~/Dropbox/hacker2): ./crack 50yoN9fp966dU
 *      crimson
 * Assumptions: Users passwords are in plaintext, are no longer than eight
 * chracters long, the passwords were typed by a user using a keybord, so there 
 * are 95 possible values for each character (ASCII characters, form space[32]
 * to tilde[127]), hence 6704780954517121 potencial passwords (1 + 95 + 95^2 +
 * 95^3 + ... 95^8). The encrypted password hash <$SALT$ENCRYPTED> is is a
 * constant string, a series of 13 printable ASCII characters, the first two
 * characters of the hash represent the salt. The user has access to the
 * dictionary file -> ./usr/share/dict/words. 
 * 
 ******************************************************************************/

#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <unistd.h>
#include <crypt.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cs50.h>
#include <string.h>

FILE *fptr_wiki;

/***
 * constants
 */
static const char alphabet[] = "abcdefghijklmnopqrstuvwxyz" 
                               "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                               "0123456789"
                               "\"`~!@#$%^&*()_-+={}[]\\/|<>,.;:? ";
static const int alphabet_size = sizeof(alphabet) - 1;

/***
 * Function prototypes
 */
int compare_strings(char s1[], char s2[]);
void cpy_n_pst(char cpy[], int strt_cpy, int end_cpy, char pst[], int strt_pst);

/***
 * global variables
 */        
bool match = false;
                  
int main(int argc, char *argv[])
{
    bool is_ascii(char str[]);
    void encryption_match(char word[], char slt[], char encrypted_pwd[], 
                      FILE *fptr_words);
         
    /* verify contents of command-line arg's, encrypted password, is composed 
       entirely of ascii characters, string in argv[1] has a legth of 13, and
       is not empty, or more than one arg. */       
    if ( argc != 2 || ! is_ascii( argv[1]) || strlen(argv[1]) != 13 )
    {        
        printf ("\n*** An ERROR occured and the program has closed.***\n"
                "Input: ./crack <encrypted password>. \nWhere <encrypted "
                "password> must be 13 ASCII characters in length.\n");
        return 1;
    }
    
    char encrypted_pwd [strlen(argv[1])]; 
    char slt[2], word[81];
    
    cpy_n_pst(argv[1], 0, 13, encrypted_pwd, 0);    // assigns encrypted_pwd   
    cpy_n_pst(argv[1], 0, 2, slt, 0);              // assigns salt        
    
    /* altternative dictionary file is exhaustive, and contains 4,160,636
       entries. It is slow to load, and it contains commonly used passwords, and
       numbers, user names from above, and some words associated with Harvard, 
       "/home/jharvard/Dropbox/wiki.txt". */  
        
    fptr_wiki = fopen("/usr/share/dict/words", "r"); 
        if (fptr_wiki == 0)
            {
                printf("\nError opening the file requested.\n"); 
                return 1;
            }  
             
    /* fucntion calls (encryption_match), which runs a dictionary attack. If it
       fails to locate a match, it then proceeds to run a brute force attack. If
       both attacks fails the function retuns to main.*/    
       
    encryption_match(word, slt, encrypted_pwd, fptr_wiki);
        if ( match == false )
            printf ("\nMATCH NOT FOUND.\n"); 
    
    fclose(fptr_wiki);
    
    return 0;
}

/***
 * Function accepts one argument string[]. Cycles through each elemet starting at 
 * 0 until it reaches NULL, or the contents of the element is not an ASCII value
 * between values for space ( ' ', 32 ) and tilde ( '~', 126), returns bool.  
 */
bool is_ascii(char str[])
{   
    bool is_ascii_flag = false;
    int i;
    
    for ( i = 0; str[i] != '\0'; ++i )
    {
        if ( ( str[i] >= ' ' && str[i] <= '~' ) )
            is_ascii_flag = true;
        else
            return is_ascii_flag = false;            
    }    
    return is_ascii_flag;
}

/***
 * Function accepts five arguents. 1. String[] to copy from. 2. Starting element 
 * in string to copy from. 3. Ending element in string to copy from. 4. String[]
 * to paste into. 5. The starting element in string to past into.  Assumtions: 
 * string to paste into is large enough to accept copy string. String to paste
 * into will accept copy string end end in '/0'.  
 */
void cpy_n_pst(char cpy[], int strt_cpy, int end_cpy, char pst[], int strt_pst)
{
    int i, j; 
       
    for ( i = strt_cpy, j = strt_pst; i < end_cpy; ++i, ++j )
        pst[j] = cpy[i];
    
    pst[j] = '\0';
}

/***
 * Function accepts three arguments. 1. A long int to track the line number to 
 * copy. 2. String[] to copy contents into. 3. File to read line from. 
 * Assumtions: string is large enough to accept line from file. 
 */
void file_line_to_str(long int line, char str[], FILE * fptr_words)
{   
    int end, i;
    
    for ( end = i = 0; i < line; ++i )
    {
        if ( ( fgets (str, 81, fptr_words) ) == 0 ) // get line
        {
            end = 1;        // (EOF)
            break;
        }
    }
}

/***
 * Function accepts two arguments. 1. String1[] to compare. 2. String2[] to 
 * compare. The function accepts two strings starting from element 0 on each,
 * cycles through each element until reaching '\0' or if a mismatch occurs.
 * Returns one of 3 int value, -1, if String1 is smaller than String2 , 0, if 
 * String1 is equal to String2, and 1, if String1 is larger than String2.  
 */
int compare_str(char s1[], char s2[])
{
    int i = 0, answer;
    
    while ( s1[i] == s2[i] && s1[i] != '\0' && s2 != '\0' )
        ++i;
    
    if ( s1[i] < s2[i] )
        answer = -1;        // s1 < s2
    else if ( s1[i] == s2[i] )
        answer = 0;         // s1 == s2
    else
        answer = 1;         // s1 > s2
    
    return answer;
}

/***
 * Function accepts one argument. A string[] to insert '\0' into the last 
 * element. Assumtions: the final element of the string is not a needed char. 
 */
void insert_null(char str[])
{
    int i = 0;
    
    while ( i < strlen(str) )
        ++i;

    str[i - 1] = '\0';
} 

/*
 * Function accepts five arguments. 1. String[] (word) to insert extracted line
 * into. 2. String[] (salt), holding the salt key extracted from encrypted
 * password provided at execution of program. 3. String[] (encrypted_pwd)
 * encrypted password provided at execution of program argv[]. 4. File to read
 * line from. The function calls six functions. 1. file_line_to_str, which
 * searches a file list of words, extracts each word into a string. 2. 
 * insert_null. 3. crypt to encrypt the extracted word and salt into
 * temp_encrypt. 4. compare_strings which compares if argument 3 matches the 
 * temp_encrypt string. If the match the program has found the password. 5. feof
 * to check if EOF has been reached. 6. brute_sequential to activate the brute
 * force algorithm. If the match the program has found the password.
 */
void encryption_match(char word[], char slt[], char encrypted_pwd[], 
                       FILE *fptr_words)
{   
    void insert_null(char str[]);
    void brute_sequential(int max_len, char slt[], char encrypted_pwd[]);
    void file_line_to_str(long int line, char str[], FILE*);
              
    printf("\n***DICTIONARY ATTACK RUNNING***\n"); 
    
    while ( match == false )
    {
        long int line = 1;
        char *temp_encrypt; 
        /* executes if the dictionary attack did not yield a matching encrypted
           password. In a later version, a brute force attack will be placed
           prior to the execution of this code. */ 
        if ( feof(fptr_words) )
        {             
            printf("Dictionary attack failed to locate a match. \n\n*** BRUTE" 
                    "FORCE ATTACK RUNNING***\n");
            brute_sequential(8, slt, encrypted_pwd);        
            break;
        }

        file_line_to_str(line, word, fptr_words);  
        insert_null(word);
        temp_encrypt = crypt(word, slt);
        
        if ( compare_str(temp_encrypt, encrypted_pwd) == 0 )
        {            
            ++line;
            printf("PASSWORD MATCH IS: %s\n", word);
            match = true;
        }              
    }
}

/***
 * Function accepts three arguments. 1. String[] (word) to insert extracted line
 * into. 2. String[] (salt), holding the salt key extracted from encrypted
 * password provided at execution of program. 3. String[] (encrypted_pwd)
 * encrypted password provided at execution of program argv[]. The function 
 * calls four two functions. 1. crypt to encrypt the current brute force string 
 * and salt into temp_encrypt. 2. compare_strings which compares if argument 3 
 * matches the temp_encrypt string.  If the match the program has found the 
 * password..
 */
void brute_match(char word[], char slt[], char encrypted_pwd[])
{
    char *temp_encrypt;  
    
    if ( match == true )
        return;
    
    temp_encrypt = crypt(word, slt); 
    
    if ( compare_str(temp_encrypt, encrypted_pwd) == 0 )
    {        
        printf("PASSWORD MATCH IS: %s\n", word);
        match = true;        
        return;
    }              
}

/***
 * Function accepts five arguments. 1. a char pointer string, will hold the
 * current search. 2. an int index (element), where to begin the string. 3. the 
 * max depth of the search string, how many digits to begin the search. 4. a 
 * string to hold the salt. 5. a string to hold the encrypted password. Within 
 * the for loop the string[i] is assigned the alphabet[i]. The if statement, 
 * checks if intex equals max_depth - 1, indicating the sequence string is
 * unique and has not reach the max of the current depth. Else it has reached
 * the max of the current depth, and recursively calls itself, with the str,
 * the index number increases by 1, is now also increased by 1. the loop ends if
 * a match is found.
 */
void brute_implement(char* str, int index, int max_depth, char slt[], 
                     char encrypted_pwd[])
{
    void brute_match(char word[], char slt[], char encrypted_pwd[]); 
    
    int i; 
          
    for ( i = 0; i < alphabet_size; ++i )
    {
        str[index] = alphabet[i];
        
        if ( match == true )
            break;            
        else if ( index == max_depth - 1 )
            brute_match(str, slt, encrypted_pwd);
        else // recursive
            brute_implement(str, index + 1, max_depth, slt, encrypted_pwd);        
    }
}

/***
 * function accepts three arguemnts. 1. an integer indicating the length of the
 * string. 2. a string the salt. 3. the encrypted password. The function assigns
 * a buffer string length. The for loop continues until the length of the
 * max_len is satisfied (last available permutation). While inside the loop NULL
 * is assigns to the end of the string, and the function calls one function 1.
 * brute_implement. brute implement stops the for loop once it i (max depth) is
 * more than max_len (length of search). the loop ends if a match is found.
 */
void brute_sequential(int max_len, char slt[], char encrypted_pwd[])
{
    void brute_implement(char* str, int index, int max_depth, char slt[], 
                         char encrypted_pwd[]); 
                     
    char* buffer = malloc(max_len + 1);
    int i;
    
    for ( i = 1; i <= max_len; ++i)
    {   
        if ( match == true )
            break;
            
        buffer[i] = '\0';
        brute_implement(buffer, 0, i, slt, encrypted_pwd);
    }
 
    free(buffer);
}
/******************************************************************************
jharvard@appliance (~/Dropbox/cs50/week2/hacker2): clang -ggdb3 -o0 -std=c99
 -Wall -Werror crack.3.c -lcs50 -lm -lcrypt -o crack.3 -v

(~/Dropbox/cs50/week2/hacker2): ./crack.3 50wt/1.dUwGeI

***DICTIONARY ATTACK RUNNING***
Dictionary attack failed to locate a match. 

*** BRUTEFORCE ATTACK RUNNING***

PASSWORD MATCH IS: ioY3d
(~/Dropbox/cs50/week2/hacker2): ./crack.3 50bOz.XZzxr9o

***DICTIONARY ATTACK RUNNING***
Dictionary attack failed to locate a match. 

*** BRUTEFORCE ATTACK RUNNING***
PASSWORD MATCH IS: ab3A
(~/Dropbox/cs50/week2/hacker2): ./crack.3 50zPJlUFIYY0o

***DICTIONARY ATTACK RUNNING***
Dictionary attack failed to locate a match. 

*** BRUTEFORCE ATTACK RUNNING***
PASSWORD MATCH IS: 13
(~/Dropbox/cs50/week2/hacker2): ./crack.3 50q.zrL5e0Sak

***DICTIONARY ATTACK RUNNING***
PASSWORD MATCH IS: password
(~/Dropbox/cs50/week2/hacker2): ./crack.3 50yoN9fp966dU

***DICTIONARY ATTACK RUNNING***
PASSWORD MATCH IS: crimson
(~/Dropbox/cs50/week2/hacker2): ./crack.3 HA610l/.LeOak

***DICTIONARY ATTACK RUNNING***
PASSWORD MATCH IS: crimson
(~/Dropbox/cs50/week2/hacker2): ./crack.3 HAL7ye0Ms7wZY

***DICTIONARY ATTACK RUNNING***
Dictionary attack failed to locate a match. 

*** BRUTEFORCE ATTACK RUNNING***
PASSWORD MATCH IS: 1337
(~/Dropbox/cs50/week2/hacker2): ./crack.3 50NwUtF.OmQNY

***DICTIONARY ATTACK RUNNING***
Dictionary attack failed to locate a match. 

*** BRUTEFORCE ATTACK RUNNING***
PASSWORD MATCH IS: 1337
*******************************************************************************/
