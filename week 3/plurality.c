#include<stdio.h>
#include<cs50.h>
#include<math.h>
#include<string.h>


bool is_valid(string name, int argc, string argv[]);



typedef struct
{
    string name;
    int score;
}candidate;


int s1 = 0;
int s2 = 0;
int s3 = 0;
int s4 = 0;
int s5 = 0;
int s6 = 0;
int s7 = 0;
int s8 = 0;
int s9 = 0;




int main (int argc, string argv[])// command line argument
{
    candidate candidates[argc];
    if (argc < 2)
    {
        printf("Usage: ./plurality [Candidate1 ...] \n");
        return 1;
    }


    int voters = get_int("Number of Voters: ");//fragen den user nach der Anzahl an votern
    int j = 0;
    string name;
    int n = 0;

    for (j = 0; j < voters; j++)
    {
        name = get_string("Vote: ");

        if (is_valid(name, argc, argv))
        {
            for (int t = 0; t < 9; t++)
            {
                if (strcmp(argv[t], name)==0)
                {
                    candidates[t].score ++;
                }
            }
        }
        else
        {
            printf("invalid vote");
        }

    int max_score = s1;
    if (s2 > max_score)max_score = s2;
    if (s3>max_score)max_score=s3;
    if(s4>max_score)max_score=s4;
    if(s5>max_score)max_score=s5;
    if(s6>max_score)max_score=s6;
    if(s7>max_score)max_score=s7;
    if(s8>max_score)max_score=s8;
    if(s9>max_score)max_score=s9;


    if (s1==max_score)printf("%s\n",argv[1]);
    if(s2==max_score)printf("%s\n",argv[2]);
    if(s3==max_score)printf("%s\n",argv[3]);
    if(s4==max_score)printf("%s\n",argv[4]);
    if(s5==max_score)printf("%s\n",argv[5]);
    if(s6==max_score)printf("%s\n",argv[6]);
    if(s7==max_score)printf("%s\n",argv[7]);
    if(s8==max_score)printf("%s\n",argv[8]);
    if(s9==max_score)printf("%s\n",argv[9]);

    return 0;

   }
}

bool is_valid (string name,int argc,string argv[])
{

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i],name) == 0)//Das ==0 nicht vergessen
        {
            return true;
        }

    }
    return false;
}









