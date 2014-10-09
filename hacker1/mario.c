/***
 * mario.c (c) by Victor Barriga
 * 
 * mario.c is licensed under a
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 * 
 * You should have received a copy of the license along with this
 * work.  If not, see <http://creativecommons.org/licenses/by-nc-sa/3.0/>.
 * 
 * mario.c 
 * Computer Science 50
 * Problem Set 1 - Hacker 1 
 * 
 * Usage: ./mario
 *
 * Proram receives input from the user the height of half-pyramid 
 * -> prompt user for non-negative integer no larger than 23
 * For example if the input given by the user is 4, the following prints:
 * Height: 4
 *        #  #
 *       ##  ##
 *      ###  ###
 *     ####  ####
 * 
 **/

 #include <cs50.h>
 #include <stdio.h>

int main(int argc, string argv[])
{
    // declare variables for height of pyramid
    int height;
    // get height of pyramid from user
    do
    {
        printf("Please input a number between 0 and 23 for\
               the half-pyramid's height: ");
        height = GetInt();
    }
    while (height < 0 || height > 23);
    
    // declare variable for spaces and hashes to be printed per line
    int spaces = height - 1;
    int hashes = 1;
    int hashes2 = 1;
    // iterate accross to create height
    for (int i = 0; i < height; i++)
    {
        // iterate accross width for spaces
        for (int j = 0; j < spaces; j++)
            // print the character spaces
            printf(" ");
            spaces--;
                // iterate accross width for hashes
                for (int k = 0; k < hashes; k++)
                    printf("#");
                    hashes++;
                    // iterate accross for mid spaces
                    printf("  ");
                        // iterate accross width for hashes2
                        for (int m = 0; m < hashes2; m++)
                            printf("#");
                            hashes2++;
                                    
        // move on to the next line
        printf("\n");
        
    }
}
