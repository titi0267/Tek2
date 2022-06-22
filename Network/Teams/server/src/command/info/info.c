/*
** EPITECH PROJECT, 2022
** teams
** File description:
** info
*/

#include "../../../include/teams.h"

void info_command(teams_t *server, client_list_t *client)
{
    cli_create_t client_payload;

    UNUSED(server);
    read(client->fd, &client_payload, sizeof(cli_create_t));
    switch (client_payload.args_nbr) {
        case TEAMS:
            info_team(client, client_payload);
            break;
        case CHANNEL:
            info_channel(client, client_payload);
            break;
        case THREADS:
            info_thread(client, client_payload);
            break;
        default:
            info_user(client, client_payload);
            break;
    }
}