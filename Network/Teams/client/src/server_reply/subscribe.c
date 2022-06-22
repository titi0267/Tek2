/*
** EPITECH PROJECT, 2022
** teams
** File description:
** subscribe
*/

#include "../../include/teams.h"
#include "../../include/reply.h"
#include "../../include/command.h"

void r_subscribe(client_t *client)
{
    server_sub_t sub;

    memset(sub.team_uid, 0, MAX_NAME_LENGTH);
    memset(sub.user_uuid, 0, MAX_NAME_LENGTH);
    read(client->socket_fd, &sub, sizeof(server_sub_t));
    if (sub.exist == 0) {
        client_error_unknown_team(sub.team_uid);
        return;
    }
    client_print_subscribed(sub.user_uuid, sub.team_uid);
    UNUSED(client);
}