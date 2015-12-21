/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // Ensure proper usage
    if (argc != 4)
    {
        printf("Usage: resize factor infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    
    int resfa = atoi(argv[1]);
    
    if (resfa < 1 || resfa > 100)
    {
        printf("Resize factor must be from 1 to 100\n");
        return 1;
    }

   // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bfn;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bfn = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bin;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bin = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // we set the new dimensions
    bin.biWidth = bi.biWidth * resfa;
    bin.biHeight = bi.biHeight * resfa;
    
    // we set the old and the new paddings
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int new_padding = (4 - (bin.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // Determine new image sizes
    bin.biSizeImage = (bin.biWidth * sizeof(RGBTRIPLE) + new_padding) * abs(bin.biHeight);
    bfn.bfSize = bf.bfSize - bi.biSizeImage + bin.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfn, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bin, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // Read each scanline factor times
        for (int j = 0; j < resfa; j++)
        {  
            // iterate over pixels in scanline
            for (int k = 0; k < bi.biWidth; k++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile, multiplied by factor
                for (int l = 0; l < resfa; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);   
                } 
            }
            
            // Add a new padding
            for (int l = 0; l < new_padding; l++)
            {
                fputc(0x00, outptr);
            }
            
            // Return to the beginning of a scanline
            if (j < resfa - 1)
            {
                fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
            }
        }

        // Skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
