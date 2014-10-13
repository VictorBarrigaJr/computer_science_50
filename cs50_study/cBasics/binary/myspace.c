/**
 *CS50, CS50 Study, Binary
 *myspace
 *Victor Barriga
 *victorbarriga@live.com
 *Program prompts the user for a message -> output the message w/ first letter capitalized
 *thanks for the add --> ThAnKs FoR tHe AdD
 */
 
 #include <cs50.h>
 #include <stdio.h>
 #include <ctype.h>
 #include <string.h>
 
 int main (int argc, string argv[])
 {
    // get string from user
    printf("Please enter a statement: ");
    string input = GetString();
    
    bool capitalize = true;
    
    // for each character of string
    for (int i = 0, j = strlen(input); i < j; i++)
    {
        // if character is a letter
        if (isalpha(input[i]))
        {       
            // if letter should be capitalized
            if (capitalize == true)   
                // print capitalize letter
                printf("%c", toupper(input[i]));
            else            
                // print lowercase letter
                printf("%c", input[i]);
            // flip bool
            capitalize = !capitalize;
        }
        //if character is a space
        else        
            //print space
            printf("%c", input[i]);           
    }
 }
