/***************************************************************************
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 ***************************************************************************/
 
// standard libraries
#define _XOPEN_SOURCE
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    // we check if there are 2 or 3 arguments
    // and if not we print the usage of our program
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // we convert the char value to int
    int n = atoi(argv[1]);

    // if the user supplied 3 arguments,
    // we convert the 3rd argument (seed) to int
    // else the srand becomes the current time
    if (argc == 3)
    {
        srand((unsigned int) atoi(argv[2]));
    }
    else
    {
        srand((unsigned int) time(NULL));
    }

    // we generate pseudo-random numbers, n times 
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", rand() % LIMIT);
    }

    // success
    return 0;
}
