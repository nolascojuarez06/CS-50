#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE average = (round)((float)((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0));

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int Red = 0, Green = 0, Blue = 0;
            float count = 0.0;

            for (int ei = -1; ei <= 1; ei++)
            {
                for (int ej = -1; ej <= 1; ej++)
                {
                    if ((i + ei) >= 0 && (i + ei) < height && (j + ej) >= 0 && (j + ej) < width)
                    {
                        Red += temp[(i + ei)][(j + ej)].rgbtRed;
                        Green += temp[(i + ei)][(j + ej)].rgbtGreen;
                        Blue += temp[(i + ei)][(j + ej)].rgbtBlue;
                        count++;
                    }
                }
            }

            image[i][j].rgbtRed = (BYTE) round((float) Red / count);
            image[i][j].rgbtGreen = (BYTE) round((float) Green / count);
            image[i][j].rgbtBlue = (BYTE) round((float) Blue / count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int Redx = 0, Greenx = 0, Bluex = 0;
            int Redy = 0, Greeny = 0, Bluey = 0;

            for (int ei = -1; ei <= 1; ei++)
            {
                for (int ej = -1; ej <= 1; ej++)
                {
                    if ((i + ei) >= 0 && (i + ei) < height && (j + ej) >= 0 && (j + ej) < width)
                    {
                        int kernel_x = Gx[ei + 1][ej + 1];
                        int kernel_y = Gy[ei + 1][ej + 1];

                        Redx += temp[(i + ei)][(j + ej)].rgbtRed * kernel_x;
                        Greenx += temp[(i + ei)][(j + ej)].rgbtGreen * kernel_x;
                        Bluex += temp[(i + ei)][(j + ej)].rgbtBlue * kernel_x;

                        Redy += temp[(i + ei)][(j + ej)].rgbtRed * kernel_y;
                        Greeny += temp[(i + ei)][(j + ej)].rgbtGreen * kernel_y;
                        Bluey += temp[(i + ei)][(j + ej)].rgbtBlue * kernel_y;
                    }
                }
            }

            // Compute final value (sqrt(Gx² + Gy²))
            int red = round(sqrt(Redx * Redx + Redy * Redy));
            int green = round(sqrt(Greenx * Greenx + Greeny * Greeny));
            int blue = round(sqrt(Bluex * Bluex + Bluey * Bluey));

            // Clamp to 255 (maximum allowed value)
            image[i][j].rgbtRed = (red > 255) ? 255 : red;
            image[i][j].rgbtGreen = (green > 255) ? 255 : green;
            image[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
        }
    }
    return;
}
