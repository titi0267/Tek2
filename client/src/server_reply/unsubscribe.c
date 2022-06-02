/*
** EPITECH PROJECT, 2022
** teams
** File description:
** unsubscribe
*/

#include "../../include/teams.h"
#include "../../include/reply.h"
#include "../../include/command.h"

void r_unsubscribe(client_t *client)
{
    server_unsub_t unsub;

    read(client->socket_fd, &unsub, sizeof(server_unsub_t));
    if (unsub.valid == 0)
        ;//client_error_unknown_team(unsub.team_uid);
    //client_print_unsubscribed(unsub.uid, unsub.team_uid);
    UNUSED(client);
}