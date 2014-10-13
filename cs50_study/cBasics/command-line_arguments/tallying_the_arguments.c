/**
 *CS50, CS50 Study, Command-Line Arguments
 *tallyin_the_arguments
 *Victor Barriga
 *victorbarriga@live.com
 *Program prints out the total number of characters in the command line arguments.
 *Ignore whitespace
 *./a.out foo == 3 characters
 *./a.out foo bar baz == 9 characters
 *./a.out == 0 characters
*/

#include <stdio.h>
#include <string.h>


int main(int argc, string argv)
{
    // declare a variable to store a count of characters
    // initialize the variable to 0
    int len = 0;
    // for each argument that was p-assed in
    for (int i = 1; i < argc; i++)
    {
        // determine the length of argument, add to the count declared above
        len += strlen(argv[i]);
    }
    // print out the value of the count
    printf("You have entered %i charecters.\n", len);
}
