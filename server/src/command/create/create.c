/*
** EPITECH PROJECT, 2022
** teams
** File description:
** create
*/

#include "../../../include/teams.h"

void create_command(teams_t *server, client_list_t *client)
{
    cli_create_t client_payload;

    UNUSED(server);
    read(client->fd, &client_payload, sizeof(cli_create_t));
    switch (client_payload.args_nbr) {
        case TEAMS:
            create_chanel(server, client, client_payload);
            break;
        case CHANNEL:
            create_thread(server, client, client_payload);
            break;
        case THREADS:
            create_reply(server, client, client_payload);
            break;
        default:
            create_team(server, client, client_payload);
            break;
    }
}