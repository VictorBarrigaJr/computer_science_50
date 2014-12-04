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

// define blocksize jpg are saved in 512 blocks
#define BLOCKSIZE 512

// BYTE typedef equal to unsigned integer 8-bits in length.
typedef uint8_t BYTE;

int main(int argc, char* argv[])
{
    // open memory card file to read
    FILE* inptr = fopen("card.raw", "r"); 
    if (inptr == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    
    // temp output file
    FILE* outptr = NULL;
    
    // image counter
    int jpg_counter = 0;

    // marker to keep searching
    bool searching = true;

    // search for jpg repeats until end of file is reached 
    while (searching) 
    {
        // create a buffer size of BLOCKSIZE (512 bytes)- empty buffer
        BYTE buffer[BLOCKSIZE] = {};
        
        // reads inptr into buffer until EOF
        for (int i = 0; i < BLOCKSIZE; i++) 
        {
            // if EOF, close file
            if (feof(inptr))
            {
                fclose(inptr);
                // close any opened outptr
                if (outptr != NULL)
                {
                    fclose(outptr);
                }

                searching = false;
                
                return 0;
            }

            fread(&buffer[i], sizeof(BYTE), 1, inptr);            
        }

        // check if first 4 bytes match jpg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            // if previously opened outptr file exists, closes it
            if (outptr != NULL)
            {
                fclose(outptr);
            }

            // create a new jpeg file using ###.jpg naming format      
            char filename[4];
            sprintf(filename, "%03d.jpg", jpg_counter);
            jpg_counter++;

            // assign ###.jpg to outptr, open file to write, and check if empty
            if ((outptr = fopen(filename, "w")) == NULL)
            {
                printf("Could not write file.\n");
                return 2;
            }

            // write the buffer into the file
            fwrite(&buffer[0], BLOCKSIZE * sizeof(BYTE), 1, outptr);    
        }
        // copy the continued data in the buffer
        else if (outptr != NULL)
        {
            fwrite(&buffer[0], BLOCKSIZE * sizeof(BYTE), 1, outptr);
        }
    }

    // close file
    fclose(inptr);

    return 0;
}
