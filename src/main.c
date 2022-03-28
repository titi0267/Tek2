/*
** EPITECH PROJECT, 2022
** B-PSU-402-STG-4-1-strace-timothe.coniel
** File description:
** main
*/

#include "../include/main.h"

int usage(void)
{
    printf("USAGE: ./strace [-s] [-p <pid>|<command>]\n");

    return (ERROR);
}

int flags(int ac, char **av)
{
    if (strcmp("--help", av[1]) == 0)
        return (usage());
    for (int i = 1; i < ac; i++) {
        if (strcmp("-p", av[i]) == 0)
            flag_p();
        else if (strcmp("-s", av[i]) == 0)
            flag_s();
        else {
            printf("Unknown flag: %s\n", av[i]);
            return (ERROR);
        }
    }
    return (0);
}

int main(int ac, char **av)
{
    if (ac == 1)
        return (no_options());
    else
        return (flags(ac, av));
    return (0);
}