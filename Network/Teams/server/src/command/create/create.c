/*
** EPITECH PROJECT, 2022
** teams
** File description:
** create
*/

#include "../../../include/teams.h"

server_create_info_t get_create_info_struct(void)
{
    server_create_info_t create_info;

    memset(&create_info, 0, sizeof(create_info));
    memset(create_info.name, 0, MAX_NAME_LENGTH);
    memset(create_info.team_uuid, 0, MAX_NAME_LENGTH);
    memset(create_info.description, 0, MAX_DESCRIPTION_LENGTH);
    memset(create_info.channel_uuid, 0, MAX_NAME_LENGTH);
    memset(create_info.thread_uid, 0, MAX_NAME_LENGTH);
    memset(create_info.comment_body, 0, MAX_BODY_LENGTH);

    return (create_info);
}

void create_command(teams_t *server, client_list_t *client)
{
    cli_create_t client_payload;

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