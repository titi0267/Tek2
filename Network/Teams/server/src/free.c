/*
** EPITECH PROJECT, 2022
** teams
** File description:
** free
*/

#include "../include/teams.h"

void free_all(teams_t *teams)
{
    free(teams->fds);
    free_list(teams);
    free(teams);
}