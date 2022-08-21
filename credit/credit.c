#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>

bool getCardNum(void);    // prototype for card data input function
int checkCardValid();     // prototype for function to verify card number is valid
void identifyCardBrand(); // protype for card identification function

string cardData[2];     // array to store card data
char cardString[17];    // card number stored as string
bool lenValid = false;  // Boolean to verify card length is valid
bool cardValid = false; // Boolean for verification vs Luhn algorithm status

int main(void)
{
    getCardNum();
    if (lenValid == true)
    {
        checkCardValid();
    }
    if (cardValid == true)
    {
        identifyCardBrand();
    }
    else
    {
        printf("INVALID\n");
    }
}

int checkCardValid() // Run card number through Luhn algorithm
{
    int checkSum[30];
    //  TO-DO convert card number from string to INT
    // printf("Card number Integer: %lli\n",cardNum);  // Verify integer stored correctly into cardNum variable
    // printf("Card integer: %li\n",cardNum);
    int digitCount = strlen(cardData[0]); // create integer for digit counter
    // printf("Beginning card validation\n");  // Print string to show progress
    int doubled = 0;
    for (int i = 2; i <= digitCount; i += 2)
    {
        int addToSum = 0;
        int digitLookup = (digitCount - i);
        char currDigitChar = cardData[0][digitLookup];
        int currentInt = (int)(currDigitChar - 48); // Subtract 48 to offset for ASCII
        // printf("%i: %c : %c : %i\n", digitCount - i + 1, currDigitChar, cardData[0][16-i], currentInt);

        // printf("%i\n", currentInt);
        if ((currentInt * 2) >= 10)
        {
            addToSum = (int)((currentInt * 2) - 9);
            // printf("add: %i.", addToSum);
            checkSum[0] += addToSum;
            // printf("total: %i\n", checkSum[0]);
        }
        else
        {
            addToSum = currentInt * 2;
            // printf("add: %i.  Total: %i\n", addToSum, checkSum[0]);
            checkSum[0] += addToSum;
            // printf("%i", checkSum[0]);
        }
    }
    for (int i = 1; i <= digitCount; i += 2)
    {
        int digitLookup = (digitCount - i);
        char currDigitChar = cardData[0][digitLookup];
        // printf("%i: %c : %c\n", digitCount - i + 1, currDigitChar, cardData[0][16-i]);
        int currentInt = (int)(currDigitChar - '0'); // Subtract 48 to offset for ASCII
        checkSum[1] += currentInt;
    }
    // printf("doubled total: %i\n", checkSum[0]);
    int luhnIndex = checkSum[0] + checkSum[1];
    int luhnVerify = luhnIndex % 10;
    // printf("Luhn: %i\n", luhnVerify);
    if (luhnVerify == 0)
    {
        cardValid = true;
    }

    return cardValid;
}

void identifyCardBrand()
{
    if (strlen(cardData[0]) == 13) // 13 digits must be VISA
    {
        if ((cardData[0][0]) == '4')
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (strlen(cardData[0]) == 15) // 15 digits must be AMEX
    {
        if ((((cardData[0][0]) == '3') && (((cardData[0][1]) == '4') || ((cardData[0][1]) == '7'))))
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (((cardData[0][0]) == '5') && (((cardData[0][1]) == '1') || ((cardData[0][1]) == '2') || ((cardData[0][1]) == '3') || ((cardData[0][1]) == '4' || ((cardData[0][1]) == '5')))) //  Matches MC prefixes?
    {
        printf("MASTERCARD\n");
    }
    else if ((cardData[0][0]) == '4')
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

bool getCardNum(void) // Function to gather card number input
{
    long cardInt = get_long("Input card number: "); //  Gather user input for card number
    // printf("\n\n\n\n");
    sprintf(cardString, "%li", cardInt);      // Convert long integer to string using sprintf and store string as "cardStr
    cardData[0] = cardString;                 //  Transfer cardString into cardData[0] for use later
    int cardNumLen = strlen(cardString);      // Find length of card number entered and store in cardNumLen
    char cardLenString[cardNumLen];          // Temporary length holder variable to use in sprintf
    sprintf(cardLenString, "%i", cardNumLen); // Convert card length to string from int
    cardData[1] = cardLenString;              //  Store card number length in cardData[1] for later use
    if ((cardNumLen < 13 || cardNumLen > 16) || cardNumLen == 14)
    {
        printf("Invalid\n");
    }
    else
    {
        // printf("\nHere is the data from cardData\nCard number: %s\nCard Number length: %s\n", cardData[0], cardData[1]);  // Verify needed data stored in cardData array
        lenValid = true;
    }
    return lenValid;
}
