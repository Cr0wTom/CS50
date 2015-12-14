#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    string name;
    int n;
    name = GetString();
    n = strlen(name);
    
    // we print the first character as uppercase
    printf("%c", toupper(name[0]));
    
    // we loop throught all the letters
    for ( int i = 0; i < n; i++)
    {
        // we check if we are in a space character and 
        // if the next character is not a space character
        if ( name[i] == ' ' && name[i + 1] != '\0') 
        {
            // we print the rest of the initials as uppercase letters
            printf("%c", toupper(name[i + 1])); 
            // add 1 to i because we have checked the next caracter
            i++;
        }
    }
    printf("\n"); 
}
