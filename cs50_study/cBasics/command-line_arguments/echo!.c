/**
 *CS50, CS50 Study, Command-Line Arguments
 *echo!
 *Victor Barriga
 *victorbarriga@live.com
 *Program recreates the echo command in Unix.  
 *Loop through the user's argument and print them out one-by one, adding a space between them.
 *(~): echo This is CS50
 *This is CS50
*/

#include <stdio.h>

int main(int argc, char** argv)
{
    // for each command line argument
    for(int i = 1; i < argc; i++)
    {
        // print argumet, be sure to add a trailing space
        printf("%s ", argv[i]);
    }
    // add trailing newline at the end
    printf("\n");
}
