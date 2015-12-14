#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h> 
#include <stdlib.h>

int main(int argc, string argv[])
{

    // we need only 2 command line arguments, so we make the check
    if (argc != 2)
    {
        printf("Please use correct syntax; ./ceasar <key>\n");
        return 1;
    }
    else
    {   

        // we convert argv[1] from string to int
        // and define the variable that will contain our message
        int k = atoi(argv[1]);
        string message;
		
        // we get the message from the user
        // error in user friendly message in compile
        message = GetString(); 
    
        // loop for the enciphering of the message
        for (int i = 0, j = strlen(message); i < j; i++)
        {
            
            // for lowercase letters
            if (isupper(message[i]) && isalpha(message[i]))
            {
                message[i] = (message[i] - 'A' + k) % 26 + 65;
            }
			
            // for upercase letters
		    else if (islower(message[i]) && isalpha(message[i]))
            {
                message[i] = (message[i] - 'a' + k) % 26 + 97;
            }        

            printf("%c", message[i]); 
        }
		
        printf("\n"); 
    }
    
    return 0; 
}
