/*
** EPITECH PROJECT, 2022
** teams
** File description:
** connected
*/

#include "../../include/teams.h"

int is_connected(teams_t *server, char *uid)
{
    client_list_t *tmp = server->head;

    for (; tmp != NULL; tmp = tmp->next) {
        if (strcmp(tmp->uid, uid) == 0)
            return (LOGGED);
    }
    return (NOT_LOGGED);
}