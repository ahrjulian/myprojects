#include<stdio.h>
#include<cs50.h>
#include <string.h>

int i;
int main (void)
{
    int q = 0;
    int j = 0;
    string input1 = get_string("Player 1: ");
    string input2 = get_string("Player 2: ");
    int lenght2 = strlen(input2);
    int lenght1 = strlen(input1);
    for (i= 0; i<lenght1;i++)
    {
        if (input1[i] == 65)
        j++;

        if (input1[i] == 97)
        j++;

        if (input1[i] == 66)
        j = j + 3;

        if (input1[i] == 98)
        j = j + 3;

        if (input1[i] == 67)
        j = j + 3;

        if (input1[i]== 99)
        j=j+3;

        if (input1[i] == 68)
        j = j + 2;

        if (input1[i]==100)
        j=j+2;

        if (input1[i] == 69)
        j++;

        if (input1[i]==101)
        j++;

        if (input1[i] == 70)
        j = j + 4;

        if (input1[i] == 102)
        j=j+4;

        if (input1[i] == 71)
        j = j + 2;

        if (input1[i]==103)
        j=j+2;

        if (input1[i] == 72)
        j = j + 4;

        if (input1[i]==104)
        j=j+4;

        if (input1[i] == 73)
        j++;

        if (input1[i]==105)
        j++;

        if ( input1[i] == 74)
        j = j + 8;

        if (input1[i]==106)
        j=j+8;

        if (input1[i] == 75)
        j = j + 5;

        if (input1[i] == 107)
        j=j+5;

        if (input1[i] == 76)
        j++;

        if (input1[i]==108)
        j++;

        if (input1[i] == 77)
        j = j+3;

        if (input1[i]==109)
        j=j+3;

        if (input1[i] == 78)
        j++;

        if (input1[i]==110)
        j++;

        if (input1[i] == 79)
        j++;

        if (input1[i]==111)
        j++;

        if (input1[i] == 80)
        j = j + 3;

        if (input1[i]==112)
        j=j+3;

        if (input1[i] == 81)
        j = j + 10;

        if (input1[i]==113)
        j=j+10;

        if (input1[i] == 82)
        j++;

        if (input1[i]==114)
        j++;

        if (input1[i] == 83)
        j++;

        if (input1[i]==115)
        j++;

        if (input1[i] == 84)
        j++;

        if (input1[i] == 116)
        j++;

        if (input1[i] == 85)
        j++;

        if (input1[i]==117)
        j++;

        if (input1[i] == 86)
        j = j + 4;

        if (input1[i]==118)
        j=j+4;

        if (input1[i] == 87)
        j = j + 4;

        if (input1[i]==119)
        j=j+4;

        if (input1[i] == 88)
        j = j + 8;

        if (input1[i]==120)
        j=j+8;

        if (input1[i] == 89)
        j = j + 4;

        if (input1[i]==121)
        j=j+4;

        if (input1[i] == 90)
        j = j + 10;

        if (input1[i]==122)
        j=j+10;
    }
    for (i = 0; i<lenght2;i++)
    {
        if (input2[i] == 65)
        q++;

        if (input2[i]==97)
        q++;

        if (input2[i] == 66)
        q = q + 3;

        if (input2[i]==98)
        q=q+3;

        if (input2[i] == 67)
        q = q + 3;

        if (input2[i]==99)
        q=q+3;

        if (input2[i] == 68)
        q = q + 2;

        if (input2[i]==100)
        q=q+2;

        if (input2[i] == 69)
        q++;

        if (input2[i]==101)
        q++;

        if (input2[i] == 70)
        q = q + 4;

        if (input2[i]==102)
        q=q+4;

        if (input2[i] == 71)
        q = q + 2;

        if (input2[i]==103)
        q=q+2;

        if (input2[i] == 72)
        q = q + 4;

        if (input2[i]==104)
        q=q+4;

        if (input2[i] == 73)
        q++;

        if (input2[i]==105)
        q++;

        if (input2[i] == 74)
        q = q + 8;

        if (input2[i]==106)
        q=q+8;

        if (input2[i] == 75)
        q = q + 5;

        if (input2[i]==107)
        q=q+5;

        if (input2[i] == 76)
        q++;

        if (input2[i]==108)
        q++;

        if (input2[i] == 77)
        q = q + 3;

        if (input2[i]==109)
        q=q+3;

        if (input2[i] == 78)
        q++;

        if (input2[i]==110)
        q++;

        if (input2[i] == 79)
        q++;

        if (input2[i]==111)
        q++;

        if (input2[i] == 80)
        q = q + 3;

        if (input2[i]==112)
        q=q+3;

        if (input2[i] == 81)
        q = q + 10;

        if (input2[i]==113)
        q=q+10;

        if (input2[i] == 82)
        q++;

        if (input2[i]==114)
        q++;

        if (input2[i] == 83)
        q++;

        if (input2[i]==115)
        q++;

        if (input2[i] == 84)
        q++;

        if (input2[i]==116)
        q++;

        if (input2[i] == 85)
        q++;

        if (input2[i]==117)
        q++;

        if (input2[i] == 86)
        q = q + 4;

        if (input2[i]==118)
        q=q+4;

        if (input2[i] == 87)
        q = q + 4;

        if (input2[i]==119)
        q=q+4;

        if (input2[i] == 88)
        q = q + 8;

        if (input2[i]==120)
        q=q+8;

        if (input2[i] == 89)
        q = q + 4;

        if (input2[i]==121)
        q=q+4;

        if (input2[i] == 90)
        q = q + 10;

        if (input2[i]==122)
        q=q+10;
    }
    if (j==q)
    {
        printf("Tie!\n");
    }
    if (j < q)
    {
        printf("Player 2 wins!\n");
    }
    if (j > q)
    {
        printf("Player 1 wins!\n");
    }
}
