#include <stdio.h>
#include <cs50.h>

int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main (void)
{
    int cents;
    do
    {
        cents = get_int ("cents owed: ");
    }
    while (cents < 0);

    int quarters = calculate_quarters(cents);
    cents = cents -quarters*25;

    int dimes = calculate_dimes(cents);
    cents = cents - dimes*10;

    int nickels = calculate_nickels(cents);
    cents = cents - nickels*5;

    int pennies = calculate_pennies(cents);
    cents = cents - pennies*1;

    int coins = quarters + pennies + nickels + dimes;

    printf("%d\n", coins);
}


int calculate_quarters(int cents)
{
    int quarters;
    quarters = 0;
    while (cents>=25)
    {
        cents = cents -25;
        quarters = quarters +1;
    }
    return quarters;
}

int calculate_dimes(int cents)
{
    int dimes;
    dimes = 0;
    while (cents>=10)
    {
        cents = cents - 10;
        dimes = dimes + 1;
    }
    return dimes;
}

int calculate_nickels(int cents)
{
    int nickels;
    nickels = 0;
    while (cents>= 5)
    {
        cents = cents - 5;
        nickels = nickels +1;
    }
    return nickels;
}

int calculate_pennies(int cents)
{
    int pennies;
    pennies = 0;
    while (cents>=1)
    {
        cents = cents -1;
        pennies = pennies + 1;
    }
    return pennies;
}




