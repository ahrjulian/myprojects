#include<math.h>
#include<string.h>
#include<stdio.h>
#include<cs50.h>
#include<stdlib.h>

/* in probabilites.h, differnet functions return characters which can either stand for a nationality or a chromosome. Those return values are
    later used in various functions in helpers.c. */


char nationality_index_hemophilia()
{
    int nationality_index = rand() % 100;
    if (nationality_index >= 1 && nationality_index <= 15){
        return 'U';
    }
    else if (nationality_index >= 16 && nationality_index <= 22){
        return 'T';
    }
    else if (nationality_index >= 23 && nationality_index <= 28){
        return 'P';
    }
    else if (nationality_index >= 29 && nationality_index <= 33){
        return 'S';
    }
    else if (nationality_index >= 34 && nationality_index <= 37){
        return 'A';
    }
    else{
        return 'D';
    }
}


char random_chromosome_germany_male()
{
    int index = rand() % 10;
    if (index == 1){
        return 'H';
    }
    return 'X';
}

char random_chromosome_germany_female()
{
    int index = rand() % 5;
    if (index == 1){
        return 'H';
    }
    return 'X';
}

char random_chromosome_turkey_male()
{
    int index = rand() % 8;
    if (index == 1){
        return 'H';
    }
    return 'X';
}

char random_chromosome_turkey_female()
{
    int index = rand() % 4;
    if (index == 1){
        return 'H';
    }
    return 'X';
}

char random_chromosome_syria_male()
{
    int index = rand() % 9;
    if (index == 1){
        return 'H';
    }
    return 'X';
}

char random_chromosome_syria_female()
{
    int index = rand() % 5;
    if (index == 1){
        return 'H';
    }
    return 'X';
}

char random_chromosome_afghanistan_male()
{
    int index = rand() % 37;
    if (index == 1){
        return 'H';
    }
    return 'X';
}

char random_chromosome_afghanistan_female()
{
    int index = rand() % 19;
    if (index == 1){
        return 'H';
    }
    return 'X';
}

char random_chromosome_ukraine_male()
{
    int index = rand() % 5;
    if (index == 1){
        return 'H';
    }
    return 'X';
}

char random_chromosome_ukraine_female()
{
    int index = rand() % 3;
    if (index == 1){
        return 'H';
    }
    return 'X';
}

char random_chromosome_poland_male()
{
    int index = rand() % 6;
    if (index == 1){
        return 'H';
    }
    return 'X';
}

char random_chromosome_poland_female()
{
    int index = rand() % 3;
    if (index == 1){
        return 'H';
    }
    return 'X';
}

char random_chromosome_others_male()
{
    int index = rand() % 11;
    if (index == 1){
        return 'H';
    }
    return 'X';
}

char random_chromosome_others_female()
{
    int index = rand() % 5;
    if (index == 1){
        return 'H';
    }
    return 'X';
}

char random_chromosome_male()
{
    int index = rand() % 9;
    if (index == 1){
        return 'H';
    }
    return 'X';
}

char random_chromosome_female()
{
    int index = rand() % 5;
    if (index == 1){
        return 'H';
    }
    return 'X';
}


