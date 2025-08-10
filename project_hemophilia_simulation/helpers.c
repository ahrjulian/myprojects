#include<stdio.h>
#include<math.h>
#include<cs50.h>
#include<string.h>
#include "probabilities.h"
#include<stdlib.h>
#include<time.h>

/* Due to the limited memory accesability, all porbability values, birth rates, and other
   related numbers have been scaled down by 1000. */



FILE* csv_file;
FILE* csv_file_deathrate;

const int NUMBER_OF_BIRTHS = 600;//Average birthrate according to the Federal Statistical Office.


/* Each person within the population has two chromosomes, a gender, two parents,
   and one partner*/

typedef struct person
{
    char chromosome[2];
    struct person* parents[2];
    char gender;
    struct person * partner[1];
    char nationality;
}person;

/*According to the Federal Statistical office and the Oman Medical Journal, the prevelance of hemophilia A
  varies from country to country. That is why I decided adjust the probability of optaining hemophilia A based on their origin and nationatlity.
  For calculating the probability for each ethnic group, I used the Annuel Global Hemophilia Survey from 2022 as my main source. */

typedef struct
{
    char nationality;
    char male_Xchromosome;
    char first_female_Xchromosome;
    char second_female_Xchromosome;
}assign_partner_chromosomes;

int years = 40;//Simulation period in years.

char X,Y,H,F,M;//X = X-chromosome, Y = Y-chromosome, H = dysfunctional X-chromosome, F = female, M = male

/* Each character defines which nationality the person has. */
char T,U,P,S,G,A,D;//T = turkey, U = ukraine, P = poland, S = syria, G = germany, A = afghanistan, D = others

int death_rate;

int number_individuals_initial = 83600;//Population size of Germany according to the Federal Statistical Office
int number_of_male_hemophilia_patients = 4518;//Number of male hemophilia A patients in Germany according to the hemophilia register
int number_individuals_final = 0;

int date = 2024;

#define BUFFERSIZE 81

float death_rate_female[BUFFERSIZE];
float death_rate_male[BUFFERSIZE];

person *create_family(int generations);
void free_family(person*p);
person *create_partner(char partner_gender);
void print_family();
person *migrant_partner_function(char partner_gender);
void recalculate_population_size();
void open_csv_file();
void close_csv_file();
char nationality_index();
void calculate_death_rate_female();
void load_death_rate();

void open_csv_file()
{
    csv_file = fopen("hemophilia.csv", "w");
    if (csv_file == NULL)
    {
        printf("ERROR: could not open csv file");
        exit(1);
    }
    fprintf(csv_file, "population size, affected\n");
}

/* In order to incorporate the demographical change in Germany a Csv file was created to keep track of
   of many individuals from each age group life in Germany. Main source: Federal Statistical Office. */

void load_death_rate()
{
    csv_file_deathrate = fopen("death_rate.csv", "r");
    if (csv_file_deathrate == NULL){
        printf("ERRROR: could not open csv file");
        exit(1);
    }
    int index = 0;
    while(index < BUFFERSIZE && fscanf(csv_file_deathrate, "%f", &death_rate_male[index]) == 1){//read the csv file into an array
        index++;
    }
    fclose(csv_file_deathrate);
}

void calculate_death_rate_female()
{
    for (int i = 0; i < 81; i++)//In order to calculate an estimated death rate the simulation proposes that each indivdual dies at the age of 80.
    {
        death_rate_female[i] = death_rate_male[i];
    }
}

/* In create_family a new person is created. By recursivly calling the create family function. After each Generation all of the allocated memory is freeded
*/

person *create_family(int generations)
{
    char partner_Gender;
    person *new_person = malloc(sizeof(person));
    if (new_person == NULL)
    {
        printf("Memory allocation failed");
        return NULL;
    }

    if (generations > 1)
    {
        person *parent0 = create_family(generations - 1);
        if (parent0 == NULL)
        {
            return NULL;
        }

        person *parent0_partner = parent0 -> partner[0];

        new_person -> parents[0] = parent0;
        new_person -> parents[1] = parent0_partner;

        new_person -> chromosome[0] = parent0 -> chromosome[rand() % 2];//determine the chromosome of the new person -> chromosomes are inherited from the parents
        new_person -> chromosome[1] = parent0_partner -> chromosome[random() % 2];

        int nationality = rand() % 2;//determine the nationality of the new person
        if (nationality == 1){
            new_person -> nationality = parent0 -> nationality;
        }
        else{
            new_person -> nationality = parent0_partner -> nationality;
        }

        if (new_person -> chromosome[0] == 'Y' || new_person -> chromosome[1] == 'Y'){
            new_person -> gender = 'M';
            partner_Gender = 'F';
        }
        else{
            new_person -> gender = 'F';
            partner_Gender = 'M';
        }

        person *partner0;

        //determine the partner of the new person
        int is_migrant = rand() % 50;//probability according to the Federal Statisitcl Office
        if (is_migrant == 1)
        {
            partner0 = migrant_partner_function(partner_Gender);
        }
        else
        {
            partner0 = create_partner(partner_Gender);
        }

        new_person -> partner[0] = partner0;
    }
    else
    {
        /* The first person of the new generations is a healthy male*/
        //first generation
        new_person -> parents[0] = NULL;
        new_person -> parents[1] = NULL;

        new_person -> chromosome[0] = 'X';
        new_person -> chromosome[1] = 'Y';

        new_person -> gender = 'M';

        partner_Gender = 'F';
        person *partner0;

        int is_migrant = rand() % 2;
        if (is_migrant == 1)
        {
            partner0 = migrant_partner_function(partner_Gender);
        }
        else
        {
            partner0 = create_partner(partner_Gender);
        }
        new_person -> partner[0] = partner0;
    }
    if ((new_person -> gender == 'M') && (new_person -> chromosome[0] == 'H' || new_person -> chromosome[1] == 'H'))
    {
        number_of_male_hemophilia_patients++;
    }
    return new_person;
}

person *migrant_partner_function(char partner_Gender)//the migrant partner function creates a migrant partner with adjusted probabilites of obtaining hemophilia A
{
    person *new_partner = malloc(sizeof(person));
    if (new_partner == NULL)
    {
        printf("Memory allocation failed");
        return NULL;
    }
    new_partner -> gender = partner_Gender;

    new_partner -> parents[0] = NULL;
    new_partner -> parents[1] = NULL;

    //determine the nationality of the migrant partner
    char nationality_index;
    nationality_index = nationality_index_hemophilia();
    new_partner -> nationality = nationality_index;

    int TABLE_WIDTH = 6;

    assign_partner_chromosomes table[TABLE_WIDTH];

    //determine the chromosomes of the new migrant partner
    table[0].nationality = 'A';
    table[0].male_Xchromosome = random_chromosome_afghanistan_male();
    table[0].first_female_Xchromosome = random_chromosome_afghanistan_female();
    table[0].second_female_Xchromosome = random_chromosome_afghanistan_female();

    table[1].nationality = 'U';
    table[1].male_Xchromosome = random_chromosome_ukraine_male();
    table[1].first_female_Xchromosome = random_chromosome_ukraine_female();
    table[1].second_female_Xchromosome = random_chromosome_ukraine_female();

    table[2].nationality = 'T';
    table[2].male_Xchromosome = random_chromosome_turkey_male();
    table[2].first_female_Xchromosome = random_chromosome_turkey_female();
    table[2].second_female_Xchromosome = random_chromosome_turkey_female();

    table[3].nationality = 'P';
    table[3].male_Xchromosome = random_chromosome_poland_male();
    table[3].first_female_Xchromosome = random_chromosome_poland_female();
    table[3].second_female_Xchromosome = random_chromosome_poland_female();

    table[4].nationality = 'S';
    table[4].male_Xchromosome = random_chromosome_syria_male();
    table[4].first_female_Xchromosome = random_chromosome_syria_female();
    table[4].second_female_Xchromosome = random_chromosome_syria_female();

    table[5].nationality = 'D';
    table[5].male_Xchromosome = random_chromosome_others_male();
    table[5].first_female_Xchromosome = random_chromosome_others_female();
    table[5].second_female_Xchromosome = random_chromosome_others_female();

    for (int j = 0; j < TABLE_WIDTH; j++){
        if (new_partner -> nationality == table[j].nationality){
            if (new_partner -> gender == 'M'){
                new_partner -> chromosome[0] = 'Y';
                new_partner -> chromosome[1] = table[j].male_Xchromosome;
            }
            else{
                new_partner -> chromosome[0] = table[j].first_female_Xchromosome;
                new_partner -> chromosome[1] = table[j].second_female_Xchromosome;
            }
            break;
        }
    }
    return new_partner;
}

person *create_partner(char partner_Gender)//the create_partner function creates a random german partner
{
    person *new_partner = malloc(sizeof(person));
    if (new_partner == NULL)
    {
        printf("Memory allocation failed");
        return NULL;
    }

    new_partner -> gender = partner_Gender;

    new_partner -> parents[0] = NULL;
    new_partner -> parents[1] = NULL;

    if (new_partner -> gender == 'M')//determine the gender of the partner (opposite gender of the person created in the create_family function)
    {
        int random_index = rand() % 2;
        if (random_index == 1)
        {
            new_partner -> chromosome[0] = 'Y';
            new_partner -> chromosome[1] = random_chromosome_male();
        }
        else
        {
            new_partner -> chromosome[0] = random_chromosome_male();
            new_partner -> chromosome[1] = 'Y';
        }
    }
    if (new_partner -> gender == 'F')
    {
        new_partner -> chromosome[0] = random_chromosome_female();
        new_partner -> chromosome[1] = random_chromosome_female();
    }
    return new_partner;
}

void print_family()
{
    printf("Number of individuals:%d\n", number_individuals_final);
    printf("Number of male hemophilia A patients: %d\n", number_of_male_hemophilia_patients);

    if (csv_file)//store data in a csv file
    {
        fprintf(csv_file, "%d,%d\n", number_individuals_final, number_of_male_hemophilia_patients);
    }
}


void recalculate_population_size()
{
    int births = 600; //birth rate according to the Federal Statistical Office
    int immigration = 1800;//Immigration numbers in Germany according to the Federal Statisitcal Office
    int emigration = 1300;//Emigration numbers in Germany according to the Federal Statisitcal Office

    number_individuals_final = number_individuals_initial + births + immigration - emigration - death_rate; //calculate the updated population size after each year

    float hemophilia_deaths = (float)death_rate / (float)number_individuals_final; //calculate the number of hemophilia deaths based on the updated population size

    int hemophilia_death_index = (int)round(hemophilia_deaths * number_of_male_hemophilia_patients);

    number_of_male_hemophilia_patients = number_of_male_hemophilia_patients - hemophilia_death_index;//calculate the updated number of hemophilia A cases for each year that was simulated
}

void free_family(person *p)//free_family frees the allocated memory after each year
{
    if (p == NULL)
    {
        return;
    }
    free_family(p -> parents[0]);
    free_family(p -> parents[1]);

    free(p);
}

void close_csv_file()
{
    if (csv_file)
    {
        fclose (csv_file);
    }
}


