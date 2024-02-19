/*
** EPITECH PROJECT, 2022
** B-CCP-400-STG-4-1-panoramix-timothe.coniel
** File description:
** parse_args
*/

#include "../include/panoramix.h"

int check_args_village(char *nb_villagers, char *nb_fights,
    parameters_t *params)
{
    if (atoi(nb_villagers) <= 0 || atoi(nb_fights) <= 0) {
        usage();
        printf("Values must be >0.\n");
        return (ERROR_CODE);
    }
    params->nb_villager = atoi(nb_villagers);
    params->nb_fights = atoi(nb_fights);
}

int check_args_potion(char *pot_size, char *nb_refills, parameters_t *params)
{
    if (atoi(pot_size) <= 0 || atoi(nb_refills) <= 0) {
        usage();
        printf("Values must be >0.\n");
        return (ERROR_CODE);
    }
    params->pot_size = atoi(pot_size);
    params->initial_pot_size = params->pot_size;
    params->nb_refills = atoi(nb_refills);
}

int parse_args(int ac, char **av, parameters_t *params)
{
    if (ac != 5) {
        fprintf(stderr, "Error: There must be at least 4 args\n");
        return (ERROR_CODE);
    }
    if (check_args_village(av[1], av[3], params) == ERROR_CODE ||
        check_args_potion(av[2], av[4], params) == ERROR_CODE)
        return (ERROR_CODE);
}