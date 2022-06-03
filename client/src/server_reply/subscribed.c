/*
** EPITECH PROJECT, 2022
** teams
** File description:
** subscribed
*/

#include "../../include/teams.h"
#include "../../include/reply.h"
#include "../../include/command.h"

int print_team(server_subscribed_info_t subed)
{
}

void r_subscribed(client_t *client)
{
    server_subscribed_info_t subed;

    while (1) {
        read(client->socket_fd, &subed, sizeof(server_subscribed_info_t));
        if (subed.last == NOT_FOUND || (subed.is_user == 1 && subed.error == 1))
            break;
        if (subed.is_user == 0 && subed.error == 1) {
            client_error_unknown_team(subed.id);
            break;
        }
        if (subed.is_user == 1)
            client_print_user(subed.id, subed.name, subed.connected);
        else
            client_print_teams(subed.id, subed.name, subed.description);
    }
}