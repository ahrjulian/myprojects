#define _DEFAULT_SOURCE
#include<stdio.h>
#include<math.h>
#include<cs50.h>
#include<stdlib.h>
#include<string.h>
#include"helpers.c"
#include<time.h>


int main(void)
{
    int Affected[years];
    int Population_size[years];
    open_csv_file();
    load_death_rate();

    srand(time(0));

    /* After each year all of the allocated memory is freeded.*/
    for(int i = 0; i < years; i++){
        person *p = create_family(NUMBER_OF_BIRTHS);//creating a family tree with recursion
        if (p == NULL){
            printf("error");
            return 1;
        }

        calculate_death_rate_female();

        death_rate = (death_rate_male[80] + death_rate_female[80]);

        death_rate = round(death_rate);

        float buffer[81];
        float buffer_female[81];

        for (int h = 0; h < 81; h++){
            buffer[h] = death_rate_male[h];
            buffer_female[h] = death_rate_female[h];
        }

        for (int j = 0; j < 80; j++){
            death_rate_male[j + 1] = buffer[j];
            death_rate_female[j + 1] = buffer_female[j];
        }

        /* Since it is difficult how birthrates in the future are going to turn out, the current birth rate of 2023
        is added as the first element of the death_rate_male and death_rate_female array*/

        death_rate_male[0] = (688/2);
        death_rate_female[0] = (688/2);

        recalculate_population_size();

        /* The date variable was implemented to display the current year on the Webappication*/
        date = date + 1;

        printf("year: %d\n", date);

        Affected[i] = number_of_male_hemophilia_patients;

        Population_size[i] = number_individuals_final;

        print_family();

        free_family(p);//free the allocated memory 
    }
    close_csv_file();
}

