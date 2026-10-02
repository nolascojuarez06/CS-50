#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    if (argc != 2 || !only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]);
    string plaintext = get_string("Plaintext: ");

    printf("Ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        printf("%c", rotate(plaintext[i], key));
    }
    printf("\n");
}

bool only_digits(string s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

char rotate(char c, int n)
{
    if (isalpha(c))
    {
        if (islower(c))
        {
            c = (int) c - 97;
            c = ((int) c + n) % 26;
            c = (int) c + 97;
            return c;
        }
        else
        {
            c = (int) c - 65;
            c = ((int) c + n) % 26;
            c = (int) c + 65;
            return c;
        }
    }
    else
    {
        return c;
    }
}
