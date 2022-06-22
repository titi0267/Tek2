/*
** EPITECH PROJECT, 2022
** teams
** File description:
** list
*/

#include "../../../include/teams.h"

void send_last_item(client_list_t *client)
{
    server_create_info_t info = get_create_info_struct();

    info.error = LAST;
    write(client->fd, &info, sizeof(server_create_info_t));
}

void list_command(teams_t *server, client_list_t *client)
{
    cli_create_t client_payload;

    UNUSED(server);
    read(client->fd, &client_payload, sizeof(cli_create_t));
    switch (client_payload.args_nbr) {
        case TEAMS:
            list_channel(client, client_payload);
            break;
        case CHANNEL:
            list_thread(client, client_payload);
            break;
        case THREADS:
            list_reply(client, client_payload);
            break;
        default:
            list_team(client, client_payload);
            break;
    }
}