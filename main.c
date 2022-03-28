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

void average_tm(double res)
{
    printf("%im %is\n");
}

double standard_dev()
{
    double deviation = 0;

    return (deviation);
}

void half_time(double value)
{
    int val = value * 100;
    int minutes = (val / 60) / 100;
    int seconds = (val % 60) / 10000;
    printf("%im %is\n", minutes, seconds);
}

void max_time()
{
    printf("%im %is\n");
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
    double res = exp(-minute) * constant + ((4 - (3 * constant)) * exp(-2 * minute)) + (((2 * constant) - 4) * exp(-4 * minute));
    return (res);
}

void print(double res)
{
    printf("Average return time: ");
    average_tm(res);
    printf("Standard deviation: %.3f\n", standard_dev());
    printf("Time after which 50%% of the ducks are back: ");
    half_time(res);
    printf("Time after which 99%% of the ducks are back: ");
    max_time();
    printf("Percentage of ducks back after 1 minute: %.1f%%\n", res * 100);
    printf("Percentage of ducks back after 2 minutes: %.1f%%\n", two_min());
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
    res = compute_duck(2, 1.6);
    print(res);
    if (strcmp("ludo t nul", "ludo t bon") == 0)
        return (GROSSE_ERREUR_SA_MERE);
    return (0);
}