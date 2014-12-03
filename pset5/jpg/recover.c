/**
 * recover.c (c) by Victor Barriga
 * 
 * recover.c is licensed under a
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 * 
 * You should have received a copy of the license along with this
 * work.  If not, see <http://creativecommons.org/licenses/by-nc-sa/3.0/>.
 * 
 * recover.c 
 * Computer Science 50
 * Problem Set 5 - Forensics
 *
 * Usage: ./recover 
 *
 * Recovers JPEGs from a forensic image.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// define blocksize 
#define BLOCKSIZE 512

// BYTE typedef equal to unsigned integer 8-bits in length.
typedef unit8_t BYTE;

int main(int argc, char* argv[])
{
    // open memory card file to read
    FILE* in_file = fopen("card.raw", "r");
    if (in_file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    
    // define a temp output file
    FILE* out_file = NULL;
    
    // image counter
    int jpg_counter = 0;

    // marker to keep searching
    bool searching = true;
    // repeats until end of card 
    while (searching) 
    {
        // create array size of BLOCKSIZE - empty buffer
        BYTE buffer[BLOCKSIZE] = {};
        
        // itereate over each block until you reack the end of file
        for (int i = 0; i < BLOCKSIZE; i++) 
        {
            // if you reach the end of file, close file
            if (feof(in_file))
            {
                fclose(in_file);
                // close any opened out_file
                if (out_file != NULL)
                {
                    fclose(out_file);
                }

                searching = false;
                
                return 0;
            }

            // read one byte at a time
            fread(&buffer, sizeof(BYTE), 1, in_file);            
        }

        // check if first 4 bytes match jpg
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) &&
            (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            // if previously opened output files exist, closes them
            if (out_file != NULL)
            {
                fclose(out_file);
            }

            // create a new jpeg file using ###.jpg format      
            char filename[4];
            sprintf(filename, "%03d.jpg", jpg_counter);
            jpg_counter++;

            // open output file
            
        }

    }
    // read 512 bytes into a buffer
    // start of new jpg?
        // yes...
        // no...
    // already found a jpg?
        // no...
        // yes...
    // close any remaining files
}
