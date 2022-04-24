/*
** EPITECH PROJECT, 2022
** B-CCP-400-STG-4-1-panoramix-timothe.coniel
** File description:
** main
*/

#include "../include/panoramix.h"

int usage(void)
{
    printf("USAGE: ./panoramix <nb_villagers> <pot_size> ");
    printf("<nb_fights> <nb_refills>\n");
    return (ERROR_CODE);
}

int main(int ac, char **av)
{
    parameters_t *params;

    if (ac == 1)
        return (usage());
    params = malloc(sizeof(parameters_t));
    if (params == NULL || parse_args(ac, av, params) == ERROR_CODE)
        return (ERROR_CODE);
    threads(params);
    free(params);
    return (0);
}