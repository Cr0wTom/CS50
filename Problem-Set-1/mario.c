#include <stdio.h>
#include <cs50.h>

int main(void)
{

    // declaring the main and counter variables
    int height;         
    int i, s, j, k;
    
    do
    {
        printf ("Give the desired pyramid height.(Non-negative, <=23): ");
        height = GetInt();
    } while (height > 23 || height < 0);
    // for convenience, I add 2 because the pyramid starts with 2 
    // blocks an this will help me in the sharp(block) printing later
    
    height = height + 2;
       
    for (i = 2; i < height; i++)
    {
        // we substract the 2 to count from 0 for the space printing
        s = height - i - 2;
		
        for (j = 0;j <= s; j++)
        {
            // we print the spaces
            printf (" ");              
        }
        for (k = 0; k < i; k++)
        {
            // we print the sharps(blocks)
            printf ("#");       
        }
		
        // now that we have finished with this line, we change line
        printf("\n"); 
	}
	
}
