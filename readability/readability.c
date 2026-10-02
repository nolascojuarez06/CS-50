#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letter(string text);
int count_word(string text);
int count_sentence(string text);

int main(void)
{
    string text = get_string("Text: ");

    int letter = count_letter(text);
    int word = count_word(text);
    int sentence = count_sentence(text);

    float L = (letter * 100.0) / word;
    float S = (sentence * 100.0) / word;

    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = (int) round(index);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }

    return 0;
}

int count_letter(string text)
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}

int count_word(string text)
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isspace(text[i]))
        {
            count++;
        }
    }
    return count + 1;
}

int count_sentence(string text)
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}
