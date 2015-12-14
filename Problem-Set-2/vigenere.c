#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // we need only 2 command line arguments, so we make the check
    if (argc != 2)
    {
        printf("Please use correct syntax; ./vigenere <key>\n");
        return 1;
    }
    // we also get through the key to search for numbers
    else if (argv[1])
    {
        int length = strlen(argv[1]);
        for (int i = 0; i < length; i++)
        {
            if (!isalpha(argv[1][i]))
            {
                printf("Use correct syntax(only letters); ./vigenere <key>\n");
                return 1;
            }
        }
    }

    // we define our variables
    int counter = 0;
    int pointer = 0;
    string message = GetString();
    string k = argv[1];
    
    // loop for the enciphering of the message	
    for (int i = 0, j = strlen(message); i < j; i++)
    {
        // we check if the character is letter and not a space
        if (isalpha(message[i]))
        {
            pointer = counter % strlen(k);
            
            // check if character is lowercase letter
            if (islower(message[i]))
            {
                if (islower(k[pointer]))
                {
                    int a = ((message[i] - 97 + k[pointer] - 97) % 26) + 97;
                    printf("%c", a);
                }
                else
                {
                    int a = ((message[i] - 97 + k[pointer] - 65) % 26) + 97;
                    printf("%c", a);
                }
            }
            
            // check if character is uppercase letter
            if (isupper(message[i]))
            {
                if (islower(k[pointer]))
                {
                    int b = ((message[i] - 65 + k[pointer] - 97) % 26) + 65;
                    printf("%c", b);
                }
                else
                {
                    int b = ((message[i] - 65 + k[pointer] - 65) % 26) + 65;
                    printf("%c", b);
                }
            }
        // counter for counting letters and not spaces
            counter++;
        }
        else
        {
            printf("%c", message[i]);
        }
    }
    
    printf("\n");
    return 0;
}
