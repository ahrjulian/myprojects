#include<stdio.h>
#include<math.h>
#include<cs50.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

int j =0;
char c;


int main (int argc,string argv[])
{
    if (argc!=2)
    {
        printf("Usage: ./Caesar.c key\n");
        return 1;
    }


    for (int i = 0; i < strlen(argv[1]);i++)
        {
            if (!isdigit(argv[1][i]))
            {
                printf("Usage: ./Caesar.c key\n");
                return 1;
            }

        }

    int key = atoi(argv[1]);

    string p = get_string("plaintext: ");
    int len = strlen(p);
    printf("ciphertext: ");
    for (j = 0; j < len;j++)
    {
        c = p[j];
        if (isupper(c))
        {
            c = (( c - 'A' + key) % 26) + 'A'; 
            printf("%c",c);

        }
        else if (islower(c))
        {
            c = ((c - 'a' + key) % 26) + 'a';
            printf("%c",c);

        }
        else
        {
            printf("%c",c);
        }
    }
    printf("\n");
    return 0;

}


