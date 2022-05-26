/*
** EPITECH PROJECT, 2022
** teams
** File description:
** connected
*/

#include "../../include/teams.h"

int isConnected(teams_t *server, char *uid)
{
    client_list_t *tmp = server->head;

    for (; tmp != NULL; tmp = tmp->next) {
        if (strcmp(tmp->uid, uid) == 0)
            return (NOT_LOGGED);
    }
    return (LOGGED);
}