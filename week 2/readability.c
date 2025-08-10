#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>



int i = 0;
int d = 0;
int k = 0;
int o = 0;
int len = 0;

int main (void)
{
    int n = 0;
    string str = get_string("Text: "); // user input
    len = strlen(str);
    char c;
    for (i=0 ;i < len; i++)
    {
        c = str[i];
        if (isalpha(c)) n++;

        if (isspace(c)) k++;

        if (c=='.'||c=='!'||c=='?') o++; //' immer wenn es sich um einen char handelt
    }
    k++;
    float L = ((float)n/k)*100;
    float S = ((float) o/(k))*100;
    float index = 0.0588*L-0.296*S-15.8;
    int grade = round(index)/1.2308;
    if (grade < 1)
    {
        printf("Klasse 1\n");
    }
    else if (grade >= 13)
    {
        printf("Klasse 13+\n");
    }
    else
    {
        printf("Klasse %i\n", grade);
    }
    return 0;
}


