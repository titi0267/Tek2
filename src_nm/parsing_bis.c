/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-timothe.coniel
** File description:
** parsing_bis
*/

#include "../include/nm.h"

int file_error(nm_t *nm)
{
    ERROR_FILE(nm->flags[0]);
    nm->error_file += 1;
    return (-1);
}

void store_flags(int i, char **av, nm_t *nm)
{
    for (int t = 0; av[i][t] != '\0'; t++)
        nm->flags[i][t] = av[i][t];
}

int multiple_files(int ac, char **av)
{
    int z = 0;

    for (int i = 1; i < ac; i++) {
        if (av[i][0] != '-')
            z++;
    }
    if (z > 1)
        return (1);
    return (0);
}
