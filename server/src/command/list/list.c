/*
** EPITECH PROJECT, 2022
** teams
** File description:
** list
*/

#include "../../../include/teams.h"

void create_command(teams_t *server, client_list_t *client)
{
    cli_list_t client_payload;

    read(client->fd, &client_payload, sizeof(cli_list_t));
    switch (client_payload.use_arg) {
        case TEAMS:
            break;
        case CHANNEL:
            break;
        case THREADS:
            break;
        default:
            break;
    }
}