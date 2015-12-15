/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{

    int point1 = 0;
    // we start counting from 0
    int point2 = n - 1; 
    int mid = (point1 + point2) / 2;

    while (point1 <= point2)
    {

        if (values[mid] == value)
        {
            return true;
	    }
        else if (value < values[mid])
        {
            point2 = mid - 1;
            mid = (point1 + point2) / 2;
        }
        else if (value > values[mid])
        {
            point1 = mid + 1;
            mid = (point1 + point2) / 2;
        }
        else 
            break;
    }

    return false;

}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{

    for (int i = 0; i < n - 1; i++) 
    {
        int check = 0;
        for (int k = i; k < n; k++) 
        {
            if (values[k] < values[i])
            {
                int temp = values[k];
                values[k] = values[i];
                values[i] = temp;
                check = 1;
            }
        }
        if (check == 0)
        {
            break;
        }
    }
    for (int j = 0; j < n; j++)
    {
        printf("%d\n", values[j]);
    }
    return;
}
