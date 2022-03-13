/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-timothe.coniel
** File description:
** main
*/

#include <stdio.h>
#include "../include/nm.h"

void usage()
{
    printf("Usage :\n");
}

char *strdup(const char *c)
{
    char *dup = malloc(strlen(c) + 1);

    if (dup != NULL)
       strcpy(dup, c);

    return dup;
}

int free_func(nm_t *nm)
{
    int z = nm->error_file;

    for (int i = 0; i <= nm->flag_nbr; i++)
        free(nm->flags[i]);
    free(nm->flags);
    free(nm);
    if (z != 0)
        return (ERROR);
    return (0);
}

int main(int ac, char **av)
{
    nm_t *nm = malloc(sizeof(nm_t));

    if (nm == NULL)
        return (ERROR);
    nm->flag_nbr = 0;
    nm->error_file = 0;
    nm->file_nbr = 0;
    if (ac == 1)
        usage();
    if (ac > 1) {
        if (parse_args(ac, av, nm) == ERROR)
            usage();
    }
    return (free_func(nm));
}