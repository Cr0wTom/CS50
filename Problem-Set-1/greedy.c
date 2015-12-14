#include <stdio.h>
#include <cs50.h>

int main(void)
{
    
    // Declaring my change variables and counter
    
    float change;
    int changeint;
    int count;

    do 
    {
        printf ("How much change is owed?\n");
        change = GetFloat();
        if (change == 0 || change <= 0)
        {
            printf ("Please give a possitive number for change.\n");
		}
    } while (change <= 0);          
    // while the change is negative, we recheck for the change value
    
    changeint = change * 1000;
    // multiplying by 1000 because of the float 
    // rounding bug that appears with the by 100 multiplication
	
    changeint = changeint / 10;
    // dividing with 10 to make the new change variable in hundrends
   
    count = 0;
    
    // checking for quarters ammount 
    // if the change amount is bigger or equal to 25
    while ( changeint >= 25 )
    {
        changeint = changeint - 25;
        count = count + 1;
    }
    
    // checking for dimes ammount if the 
    // change amount is bigger or equal to 25
    while ( changeint >= 10 )        
    {
        changeint = changeint - 10;
        count = count + 1;
    }
    
    // checking for nickels ammount if 
    // the change amount is bigger or equal to 25
    while ( changeint >= 5 )        
    {
        changeint = changeint - 5;
        count = count + 1;
    }
	
    // the pennies check can be done just by 
    // adding up the rest of the change in the count
    count = count + changeint;

    printf("%d\n", count);

}
