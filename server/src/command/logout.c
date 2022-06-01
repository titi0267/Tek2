/*
** EPITECH PROJECT, 2022
** teams
** File description:
** logout
*/

#include "../../include/teams.h"

void logout(teams_t *server, client_list_t *client)
{
    cli_logout_t logout;

    UNUSED(server);
    read(client->fd, &logout, sizeof(cli_logout_t));
    if (strlen(client->uid) != 0)
        server_event_user_logged_out(client->uid);
}