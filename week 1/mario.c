#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>


int Space;

int main (void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    for (int i = 0; i < height; i++)
    {
        for (Space = 0; Space < height - i - 1; Space++)
        {
            printf(" ");
        }
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        printf ("  ");
        for (int h = 0; h < i + 1; h ++)
        {
            printf("#");

        }
        printf("\n");
    }
}
