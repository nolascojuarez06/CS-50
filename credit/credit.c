#include <cs50.h>
#include <stdio.h>
#include <string.h>

int check(const char *card_number)
{
    int add = 0;
    int length = strlen(card_number);
    int double_digit = 0;

    for (int i = length - 1; i >= 0; i--)
    {
        int digit = card_number[i] - '0';

        if (double_digit)
        {
            digit = digit * 2;
            if (digit > 9)
            {
                digit = digit - 9;
            }
        }
        add = add + digit;
        double_digit = !double_digit;
    }
    return (add % 10 == 0);
}

string get_card_type(const char *card_number)
{
    int length = strlen(card_number);

    if ((length == 15) && (card_number[0] == '3') &&
        (card_number[1] == '4' || card_number[1] == '7'))
    {
        return "AMEX";
    }
    else if ((length == 16) && (card_number[0] == '5') &&
             (card_number[1] >= '1' && card_number[1] <= '5'))
    {
        return "MASTERCARD";
    }
    else if ((length == 13 || length == 16) && (card_number[0] == '4'))
    {
        return "VISA";
    }
    else
    {
        return "INVALID";
    }
}

int main(void)
{
    char *card_number = get_string("Number: ");

    if (check(card_number))
    {
        printf("%s\n", get_card_type(card_number));
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}
