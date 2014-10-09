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
 * Problem Set 1 
 * 
 * Usage: ./mario
 *
 * Proram receives input from the user by asking how the height of the desired
 * half-pyramid -> prompt user for non-negative integer no larger than 23.
 * For example if the user input is 8, the terminal will display: 
 * Height: 8
 *        ##
 *       ###
 *      ####
 *     #####
 *    ######
 *   #######
 *  ########
 * #########
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
        printf("How high do you want your pyramid to be? \
               Please input a number between 0 and 23: ");
        height = GetInt();
    }
    while (height < 0 || height > 23);
    
    // declare variable for spaces and hashes to be printed per line
    int spaces = height - 1;
    int hashes = 2;
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
        // move on to the next line
        printf("\n");
    }
}
