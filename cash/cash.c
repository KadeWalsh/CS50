#include <cs50.h>
#include <stdio.h>
#include <math.h>
int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - (quarters * 25);

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - (dimes * 10);

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - (nickels * 5);

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - (pennies * 1);

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    bool isValid = false;
    int change;
    while (isValid == false)
    {
        change = get_int("Change owed: ");
        if (change > 0)
        {
            isValid = true;
        }
    }
    return change;
}

int calculate_quarters(int cents)
{
    int q = round(cents / 25); // calculate number of quarters in cents
    return q; // return result
}

int calculate_dimes(int cents)
{
    int d = round(cents / 10); // calculate number of dimes in remaining cents
    return d; // return result
}

int calculate_nickels(int cents)
{
    int n = round(cents / 5); // calculate number of nickels in remaining cents
    return n; // return result
}

int calculate_pennies(int cents)
{
    int p = cents;
    return p;
}
