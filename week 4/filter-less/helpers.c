#include "helpers.h"
#include <stdint.h>
#include <stdio.h>
#include <math.h>

typedef uint8_t Byte;

typedef struct
{
    uint8_t bytes[3];
}int24_t;

int i;
int j;
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            //hier kommt der code him
            int average = round((float)(image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j]. rgbtGreen)/3);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
        }
    }
    return;//grayscale funktioniert
}

// Convert image to sepia
void sepia(int height, int width,RGBTRIPLE image[height][width])
{
    for (int z = 0; z < height; z++)
    {
        for (int u = 0; u < width; u++)
        {
            int originalRed = image[z][u].rgbtRed;
            int originalGreen = image[z][u].rgbtGreen;
            int originalBlue = image[z][u].rgbtBlue;

            int sepiaRed = round(.393 *originalRed + .769 *originalGreen + .189 *originalBlue);
            int sepiaGreen = round(.349 *originalRed + .686 *originalGreen + .168 *originalBlue);
            int sepiaBlue = round(.272 *originalRed + .534 *originalGreen + .131 *originalBlue);

            sepiaRed = (sepiaRed > 255) ? 255 : sepiaRed;
            sepiaGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            sepiaBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;

            image[z][u].rgbtRed = sepiaRed;
            image[z][u].rgbtGreen = sepiaGreen;
            image[z][u].rgbtBlue = sepiaBlue;
       }
    }
    return;
}//sepia funktioniert

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int k = 0; k < height; k++)
    {
        for (int h = 0; h < width / 2; h++)
        {
            RGBTRIPLE temp = image [k][h];
            image [k][h] = image [k][width - h - 1];
            image [k][width - h - 1] = temp;
        }
    }
    return;
}//refelct funktioniert

// Blur image funktioniert noch nicht weil es corner oder edge pixel nicht richtig blured
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int newRed, newGreen, newBlue;
    RGBTRIPLE copy[height][width];
    for (int Höhenvariable = 0; Höhenvariable < height; Höhenvariable++)
    {
        for (int Breitenvariable = 0; Breitenvariable < width; Breitenvariable++)
        {
            copy[Höhenvariable][Breitenvariable] = image[Höhenvariable][Breitenvariable];

        }

    }
    for (int h = 0; h < height; h++)
    {
        for (i = 0; i <width; i++)
        {
            int neighbouringPixels = 0;
            newRed = 0;
            newGreen = 0;
            newBlue = 0;
            for (int r = -1; r <= 1; r++)
            {
                for (int s = -1; s <= 1; s++)
                {
                    int newH = h + r;
                    int newI = i + s;
                    if (newH >= 0 && newH < height && newI >= 0 && newI < width)
                    {
                        newRed += copy[newH][newI].rgbtRed;
                        newGreen += copy[newH][newI].rgbtGreen;
                        newBlue += copy[newH][newI].rgbtBlue;
                        neighbouringPixels ++;
                    }
                }
            }
            image[h][i].rgbtRed = round(newRed / (float)neighbouringPixels);
            image[h][i].rgbtGreen = round(newGreen /(float)neighbouringPixels);
            image[h][i].rgbtBlue = round(newBlue / (float)neighbouringPixels);
        }


    }

    return;
}
