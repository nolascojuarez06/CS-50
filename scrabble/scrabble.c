#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int score(string player);

int main(void)
{
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");

    int score1 = score(player1);
    int score2 = score(player2);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int score(string player)
{
    int scr = 0;

    for (int i = 0, len = strlen(player); i < len; i++)
    {
        if (isupper(player[i]))
        {
            scr += points[player[i] - 'A'];
        }
        else if (islower(player[i]))
        {
            scr += points[player[i] - 'a'];
        }
    }
    return scr;
}
