#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char encode(char character, int key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    string keyString = argv[1]; // store key from command line argument into keyString
    for (int i = 0; i < strlen(keyString); i++)
    {
        if (!isdigit(keyString[i]))
        {
            printf("Please use a numeric key from command line.\n");
            return 1;
        }
        else
        {

        }
    }

    int key = (atoi(keyString) % 26);
    char *plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        printf("%c", encode(plaintext[i], key));
    }
    printf("\n");
}

char encode(char character, int key)
{
    if (isalpha(character)) // check if current letter is alphabetical
    {
        // if alphabetical
        character += key; // add encryption key to value
        if (!isalpha(character))
            // check for alphabetical value again
        {
            // if not alphabetical
            character -= 26; //
        }
    }
    return character;
}