/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(void)
{
    // we open the file
    FILE* fp;
    fp = fopen("card.raw", "r");	
        
        
    if (fp == NULL)
    {	
        fclose(fp);
        fprintf(stderr, "Could not open the file.\n");
        return 1;
    }

    // we set the first four bytes of every jpeg file.
    uint8_t jpeg1[4] = {0xff, 0xd8, 0xff, 0xe0};
    uint8_t jpeg2[4] = {0xff, 0xd8, 0xff, 0xe1};

    // we count the jpegs we find
    int count = 0;
    int opn = 0;
    FILE* otp;

    // we read the 512 byte blocks from file.
    uint8_t buff[512];
    uint8_t chck[4];
    fread(buff, 512, 1, fp);	

    while(fread(buff, 512, 1, fp) > 0)
    {
        // we add the first four bytes to the check buffer
        for(int i = 0; i < 4; i++)
        {
            chck[i] = buff[i];
        }

        // we check for one of the jpeg signatures
        if ((memcmp(jpeg1, chck, 4) == 0 ) || (memcmp(jpeg2, chck, sizeof(chck)) == 0))
        {
            // make the name of the file
            char file[8];
            sprintf(file, "%03d.jpg", count);

            if (opn == 0)
            {
                otp = fopen(file, "w");
                fwrite(buff, sizeof(buff), 1, otp);
                opn = 1;
            }
            if (opn == 1)
            {
                fclose(otp);
                otp = fopen(file, "w");
                fwrite(buff, sizeof(buff), 1, otp);
                count++;
            }
        }
        else
        {
            if (opn == 1)
            {
                fwrite(buff, sizeof(buff), 1, otp);
            }
        }
    }
    
    // we close the streams and exit
    if (otp)
    {
        fclose(otp);
    }

    fclose(fp);
    return 0;
}
