#include<stdio.h>
#include<cs50.h>
#include<math.h>
#include<string.h>


int main (int argc, string argv[]);
//functions
bool vote (int voter, int argc, string argv[]);
bool eliminated (int min, int argc, string argv[]);
void tabulate (void);
bool print_winner (int argc, string argv);
int is_valid_vote(char vote, int argc, char* argv[]);
//9 candidates at max
int max_score;


typedef struct
{
    string name;
    int votes;
    bool eliminated;
}candidate;//candidate ist in diesem Fall ein Datentyo ähnlich wie ein int oder ein string

typedef struct
{
    char firstpreference;
    char secondpreference;
    char thirdpreference;
}preference;


bool is_tie (int min, int argc);
int find_min(int min, int argc, string argv);
int Max_votes;
int Max_candidates = 9;
//6 verschiedene Funktionen sind nötig
candidate candidates[9];
//candidate candidates [Max_votes][Max_candidates]
//preferences [i] [j] is the candidate index of voters is preference 1
int main (int argc, string argv[])
{
    int len = argc;
    string firstpreference=NULL;
    string secondpreference=NULL;
    string thirdpreference=NULL;
    int Mehrheit = (argc + 1)/2;
    if (argc < 2)
    {
        printf("Usage: ./runoff [candidate,...]\n");
        return 1;
    }

    candidate c;

    int voters = get_int ("number of voters: ");
    preference preferences[voters];
    preference p;

    int min = 0;
    int voter;
    int i = 0;
    int j = 1;

    for (i = 0; i < voters; i++)
    {
       do
       {
        preferences[i].firstpreference = get_char ("first vote: ");//irgendo ist hier ein unendlicher loop
       }while (!is_valid_vote(preferences[i].firstpreference, argc, argv));

       do
       {
        preferences[i].secondpreference = get_char("second vote ");
       }while (!is_valid_vote(preferences[i].secondpreference, argc, argv));

       do
       {
        preferences[i].thirdpreference = get_char("third vote: ");
       }while (!is_valid_vote(preferences[i].thirdpreference, argc, argv));
    }
//hier fertig machen ertstmal?
    if (c.eliminated == false)
     {
         for (int k = 0; k < argc; k++)
        {
              if (c.votes == min)
              {
                   c.eliminated = true;
              }
        }
     }

     min = candidates[1].votes;
    for (int s = 0; s < argc; s++)
     {
        if (c.eliminated == false)
        {
             if(candidates[s].votes > min)
             {
             min = candidates[s].votes;
             }
        }
     }
    if (c.votes == min)
    {
        c.eliminated = true;
    }

    nochmal:
    if (c.votes != Mehrheit)//Wenn ein Kandidat nicht die Mehrheit hat wird die zweite preference des eliminierten Kandidaten angeschaut und quasi als eine erste preference gewärtet
    {
        for (int z = 0; z < argc; z++)
        {
            if (c.eliminated == true)
            {
                if (strcmp(candidates[z].name, &firstpreference[i])==0)
                {
                    for (int s = 0; s < 9;s++)
                    {
                        if (strcmp(candidates[s].name, &secondpreference[i])==0)
                        {
                            candidates[s].votes ++;
                        }

                    }
                    for (int s = 0; s < argc;s++)
                    {
                        if(candidates[s].eliminated == true)
                        {
                            if(candidates[s].votes < min)
                            {
                                min = candidates[s].votes;
                            }
                        }
                    }
                    if (c.votes == min)
                    {
                        c.eliminated = true;
                    }
                }
            }
        }
    }
    if (c.votes != Mehrheit)//das ist vom syntax her nicht korrekt
    {
        goto nochmal;
    }
    int Stelle;
    max_score = candidates[1].votes;
    for(int n = 0; n < argc; n++)
    {
        if (candidates[n].votes > max_score)
        {
            max_score = candidates[n].votes;
            Stelle = n;
        }

    }
    printf("%s has %d votes and is the winner of the election\n", candidates[Stelle].name, max_score);
    return 0;

}
//first function ist die bool vote function mithilfe wir im command line argument nach den eingegebenen Preferenzen suchen.

int is_valid_vote (char vote, int argc, char* argv[])
{
    int t;
    for(t = 0; t < argc; t++)
    {
        if (strcmp(argv[t], &vote)==0)
        {
            return 1;
        }
    }
    return 0;
}
bool vote (int voter, int argc, string argv[])
{
    candidate c;
    string firstpreference=NULL;
    string secondpreference=NULL;
    string thirdpreference=NULL;
    int i = 0;
    for (int j = 0; j < argc ; j++)
    {//was genau macht dieses & Zeichen?
        if (strcmp(argv[j], &firstpreference[i])==0 || strcmp(argv[j], &secondpreference[i])==0 || strcmp(argv[j], &thirdpreference[i])==0)
        {
            return true;
            //first/second oder thirdpreference existiert
        }
    }
    return false;
}
// unsere zweite function legt fest, ob ein Kandidat eliminiert wurde.
bool eliminated (int min, int argc, string argv[])
{
    candidate c;
    if (c.eliminated == false)// das statement muss ich definitiv überarbeiten
    {
        for (int k = 0; k < argc; k++ )
        {
            if (c.votes == min)
            {
                return true;
            }
        }

        return false;
    }
    else
    {
        return false;
    }
}

// tabulate function : Updates vote count for all non - eliminated candidates
// each voter votes for their highest preference candidate who has not yet been eliminated
//.....tabulate void function.....
//if any candidate has more than half the votes print out their name and return true
bool print_winner (int argc,string argv)
{
    candidate c;
    int Stelle;
    max_score = candidates[1].votes;
    for (int n = 0; n < argc;n++)
    {
        if (candidates[n].votes > max_score)
        {
            max_score = argv[n];
            Stelle = n;
        }
    }
    printf("%s has %d and is the winner of the election\n", candidates[Stelle].name, max_score);
    return true;
}
//return the minimum number of votes of any still in the election (candidates that are not eliminated yet)
int find_min (int min,int argc,string argv)
{
    candidate c;
    min = candidates[1].votes;
    for (int s = 0; s < argc; s++)
    {
        if (c.eliminated == false)
        {
            if (candidates[s].votes > min)
            {
                min = candidates[s].votes;
            }
        }
    }
    return 0;
}

bool is_tie (int min, int argc)
{
    return 0;

}

// wichtige Frage: Wie erstellt man einen array von structs und wie kann man anschließend auf diese zugreifen?
