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
    
    // calculates factored bfSize
    bf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 
        factor * (bf.bfSize - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER));

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // scaled file info
    bi.biWidth = factor * bi.biWidth;
    bi.biHeight = factor * bi.biHeight;
    bi.biSizeImage = factor * bi.biSizeImage;

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int in_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE) / factor) % 4) % 4;
    int out_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines by read file once and write n times
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int counter = 0; counter < factor; counter++)
        {
            // iterate over pixels in scanline and write n times
            for (int j = 0; j < bi.biWidth / factor; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                for (int k = 0; k < factor; k++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
        
            // skip over padding, if any
            fseek(inptr, in_padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < out_padding; k++)
            {
                fputc(0x00, outptr);
            }

            // return the indicator back
            fseek(inptr, - (bi.biWidth * 3 / factor + in_padding), SEEK_CUR);
        }

        // reset indicator to the next line
        fseek(inptr, bi.biWidth * 3 / factor + in_padding, SEEK_CUR);
        
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
