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
    if (unsub.valid == 0) {
        client_error_unknown_team(unsub.team_uid);
        return;
    }
    client_print_unsubscribed(unsub.user_uuid, unsub.team_uid);
    UNUSED(client);
}