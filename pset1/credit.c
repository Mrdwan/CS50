#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

int main(void)
{
    long cardNumber;
    long number;
    long oddNumber;
    int counter = 0;
    int sum = 0;
    long digit = 0;
    int firstTwoDigits = 0;
    int firstOneDigit = 0;

    // get user credit
    do
    {
        cardNumber = get_long("card:");
    }
    while (cardNumber <= 0);

    // assign credit to another var
    number = cardNumber;

    // count credit
    while (number != 0)
    {
        if (counter % 2 == 0)
        {
            sum += number % 10;
        }
        else
        {
            // odd
            oddNumber = (number % 10) * 2;

            if (oddNumber < 9)
            {
                sum += oddNumber;
            }
            else
            {
                while (oddNumber > 0)
                {
                    sum += oddNumber % 10;
                    oddNumber = oddNumber / 10;
                }
            }
        }

        // remove last digit then count
        number = number / 10;
        counter++;
    }

    if (sum % 10 != 0)
    {
        // die if invalid algorithm
        printf("INVALID\n");
        exit(0);
    }

    if (counter == 13)
    {
        firstOneDigit = cardNumber / 1000000000000;

        if (firstOneDigit == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    if (counter == 15)
    {
        // american
        digit = cardNumber / 10000000000000;
        if (digit == 34 || digit == 37)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (counter == 16)
    {
        firstTwoDigits = cardNumber / 100000000000000;
        firstOneDigit = cardNumber / 1000000000000000;

        if (firstTwoDigits == 51 || firstTwoDigits == 52 || firstTwoDigits == 53 || firstTwoDigits == 54 || firstTwoDigits == 55)
        {
            printf("MASTERCARD\n");
        }
        else if (firstOneDigit == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}