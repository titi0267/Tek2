/*
** EPITECH PROJECT, 2022
** teams
** File description:
** free
*/

#include "../include/teams.h"

void free_all(client_t *client, char *buff)
{
    free(buff);
    free(client);
}