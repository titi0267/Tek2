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

    read(client->socket_fd, &sub, sizeof(server_sub_t));
    if (sub.exist == 0)
        ;//client_error_unknown_team(sub.team_uid);
    //client_print_subscribed(sub.uid, sub.team_uid);
    UNUSED(client);
}