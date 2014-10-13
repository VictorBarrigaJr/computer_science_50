/**
 * CS50 Study, memory management, pointers
 * strchr.c
 *
 * Victor Barriga
 * victorbarriga@live.com
 * 
 * function that returns a substring of a C string that starts with a given 
 * character. if char is not in string return NULL
 *
 */
 
#include <stdio.h>
#include <cs50.h>
 
char* my_strchr(char* str, char c);
 
int main(void)
{
   printf("String: ");
   char* str = GetString();
   printf("Character: ");
   char c = GetChar();
   printf("Looking for substring...\n");
   char* result = my_strchr(str, c);
   if (result ==NULL)
   {
       printf("Couldn't find %c.\n", c);
   }
   else
   {
       printf("Substing: %s \n", result);
   }
}
 
char* my_strchr(char* str, char c)
{
    // itereate through string
    for (char* ptr = str; *ptr != '\0'; ptr++)
    {
        // if c is found
        if (*ptr == c)
        {
            // return substring
            return ptr;
        }
    }
    // if c wasn't found return NULL
    return NULL;
}
