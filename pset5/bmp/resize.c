/*******************************************************************************
 * resize.c (c) by Victor Barriga
 * 
 * resize.c is licensed under a
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 * 
 * You should have received a copy of the license along with this
 * work.  If not, see <http://creativecommons.org/licenses/by-nc-sa/3.0/>.
 * 
 * resize.c 
 * Computer Science 50
 * Problem Set 5 - Forensics
 *
 * Usage: ./resize n infile outfile
 *
 * Program resizes a 24-bit uncompressed BMP's by a factor of n.  The program 
 * accepts three command-line arguments, whreby n must be a positive interger 
 * less than or equal to 100, the second is the file to be resized, and the 
 * third the name of the rezised version to be written. 
 **/
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    // assign and ensure resize factor input by user is within range
    int factor = atoi(argv[1]);
    if(factor < 1 || factor > 100)
    {
        printf("Usage: ./resize n infile outfile\n");
        printf(" where n is a positive integer <= 100.\n");
        return 2;
    }

    // remember filenames 
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    // variables for original width and height
    int inptr_Width = bi.biWidth;
    int inptr_Height = bi.biHeight;
   
    // update width and height by factor
    bi.biWidth *= factor;
    bi.biHeight *= factor;
       
    // determine padding for scanlines
    int inptr_padding =  (4 - (inptr_Width * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // update image size
    bi.biSizeImage = abs(bi.biHeight) * ((bi.biWidth * sizeof (RGBTRIPLE)) + padding);
    
    // update file size
    bf.bfSize = bi.biSizeImage + sizeof (BITMAPFILEHEADER) + sizeof (BITMAPINFOHEADER); 

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // buffer to hold scanline
    RGBTRIPLE *buffer = malloc(sizeof(RGBTRIPLE) * (bi.biWidth));

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(inptr_Height); i < biHeight; i++)
    {
        int counter = 0;
        // iterate over pixels in scanline and write n times
        for (int j = 0; j < inptr_Width; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // write pixel to buffer n times
            for(int k = 0; k < factor; k++)
            {
                *(buffer + (counter)) = triple;
                counter++;
            }
        }
            
        // skip over padding, if any
        fseek(inptr, inptr_padding, SEEK_CUR);

        // write RGB triple to outfile
        for(int l = 0; l < factor; l++)
           {
               fwrite((buffer), sizeof(RGBTRIPLE), bi.biWidth, outptr);

               // write padding to outfile
               for (int m = 0; m < padding; m++)
               {
                   fputc(0x00, outptr);
               }
           }        
    }

    // free buffer
    free(buffer);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
