/*
** EPITECH PROJECT, 2022
** B-MAT-400-STG-4-1-203hotline-timothe.coniel
** File description:
** main
*/

#include "hotline.h"

int usage(void)
{
    printf("USAGE\n    ./203hotline [n k | d]\n\nDESCRIPTION\n");
    printf("    n      n value for the computation of C(n, k)\n");
    printf("    k      k value for the computation of C(n, k)\n");
    printf("    d      average duration of calls (in seconds)\n");
    return (ERROR);
}

long unsigned int factorial(int n)
{
    long unsigned int f = 1;

    for (int c = 1; c <= n; c++)
        f = f * c;
    printf("f = %i\n", f);
    return (f);
}

long unsigned int formula(int n, int k)
{
    printf("n = %i\n", n);
    return (factorial(n) / ((factorial(k) * factorial(n - k))));
}

void combinations(char **av)
{
    printf("%s-combinations of a set of size %s:\n%ld", av[1], av[2], formula(atoi(av[1]), atoi(av[2])));
}

float binomial()
{
    return (0);
}

void laws(void)
{
    printf("Binomial distribution:\n");
    for (int i = 0; i <= 50; i++) {
        if (i < 10)
            printf("%i -> %2.3f     ", i, binomial());
        else
            printf("%i -> %2.3f    ", i, binomial());
        if (i % 5 == 0)
            printf("\n");
    }
}

int main(int ac, char **av)
{
    if (ac == 1)
        return (ERROR);
    if (ac == 2 && strcmp("-h", av[1]) == 0)
        return (usage());
    if (ac == 3)
        combinations(av);
    if (ac == 2)
        laws();
}