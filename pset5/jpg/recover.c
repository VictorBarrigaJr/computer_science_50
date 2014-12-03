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
typedef uint8_t BYTE;

int main(int argc, char* argv[])
{
    // open memory card file to read
    FILE* fptr = fopen("card.raw", "r"); 
    if (fptr == NULL)
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
            if (feof(fptr))
            {
                fclose(fptr);
                // close any opened out_file
                if (out_file != NULL)
                {
                    fclose(out_file);
                }

                searching = false;
                
                return 0;
            }

            // read one byte at a time
            fread(&buffer, sizeof(BYTE), 1, fptr);            
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

            // open output file and check if empty
            if ((out_file = fopen(filename, "w")) == NULL)
            {
                printf("Could not write file.\n");
                return 2;
            }

            // write the buffer into file
            fwrite(&buffer[0], BLOCKSIZE * sizeof(BYTE), 1, out_file);    
        }
        // if outfile is opened, write buffer to the outfile
        else if (out_file != NULL)
        {
            fwrite(&buffer[0], BLOCKSIZE * sizeof(BYTE), 1, out_file);
        }
    }

    // close file
    fclose(fptr);

    return 0;
}
