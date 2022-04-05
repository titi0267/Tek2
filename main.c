/*
** EPITECH PROJECT, 2022
** B-MAT-400-STG-4-1-204ducks-timothe.coniel
** File description:
** main
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define GROSSE_ERREUR_SA_MERE 84

int usage(void)
{
    printf("USAGE\n    ./204ducks a\n\nDESCRIPTION\n    a       constant\n");
    return (GROSSE_ERREUR_SA_MERE);
}

double compute_function(int minute, double constant)
{
    //double res = exp(-minute) * constant + ((4 - (3 * constant)) * exp(-2 * minute)) + (((2 * constant) - 4) * exp(-4 * minute));
    //double res = (-0.5 * exp(-4*minute)) * (constant * (2 * exp(minute) + 1) * pow((exp(minute) - 1), 2) + 4 * exp(2 * minute) - 2);
    double res = 1 - (constant * exp(-minute) + (4 - 3 * constant)/2 * exp(-2 * minute) + ((2 * constant - 4) / 4) * exp(-4 * minute));

    return (res);
}

void print_time(double value)
{
    int minutes = floor(value);
    double seconds = fmod(value, 1) * 60;

    seconds = round(seconds);
    printf("%im %.0fs\n", minutes, seconds);
}

double average_tm(double constant)
{
    double res = 3 * ((constant + 2) / 8);

    return (res);
}

double standard_dev(double constant, double esperanzia)
{
    double res = (- 0.75 * (constant + 2) * esperanzia) + 0.4375 * (3 * constant + 2) + esperanzia * esperanzia;

    return (sqrt(res));
}

void half_time(double value)
{
    int val = value * 100;
    int minutes = (val / 60) / 100;
    int seconds = (val % 60) / 10000;
    //printf("%f\n", compute_function(3, value) * 100);

    printf("%im %is\n", minutes, seconds);
}

void max_time()
{
    printf("%im %is\n", 0, 0);
}

double one_min()
{
    double one_min = 0;

    return (one_min);
}

double two_min()
{
    double two_min = 0;

    return (two_min);
}

double compute_duck(int minute, int constant)
{
    double res = 3 * ((constant + 2) / 8);

    return (res);
}

void print(double res)
{
    printf("Average return time: ");
    print_time(average_tm(res));
    printf("Standard deviation: %.3f\n", standard_dev(res, average_tm(res)));
    printf("Time after which 50%% of the ducks are back: ");
    half_time(res);
    printf("Time after which 99%% of the ducks are back: ");
    max_time();
    printf("Percentage of ducks back after 1 minute: %.1f%%\n", compute_function(1, res)  * 100);
    printf("Percentage of ducks back after 2 minutes: %.1f%%\n", compute_function(2, res) * 100);
}

int main(int ac, char **av)
{
    double res = 0;

    if (ac != 2)
        return (GROSSE_ERREUR_SA_MERE);
    if (atof(av[1]) > 2.5 || atof(av[1]) < 0)
        return (GROSSE_ERREUR_SA_MERE);
    if (ac == 2 && av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == '\0')
        return (usage());
    print(atof(av[1]));
    if (strcmp("ludo t nul", "ludo t bon") == 0)
        return (GROSSE_ERREUR_SA_MERE);
    return (0);
}