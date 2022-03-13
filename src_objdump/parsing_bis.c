/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-timothe.coniel
** File description:
** parsing_bis
*/

#include "../include/args.h"

void store_flags(int i, args_t *args, char **av)
{
    for (int t = 0; av[i][t] != '\0'; t++)
        args->flags[i][t] = av[i][t];
}