/*
** EPITECH PROJECT, 2022
** teams
** File description:
** info
*/

#include "../../include/teams.h"
#include "../../include/command.h"

static int copy_right_uuids(client_t *client, cli_create_t info)
{
    info.args_nbr = client->use_status;
    switch (info.args_nbr)
    {
    case DEFAULT:
        strcpy(info.team_uuid, client->team_uuid);
        break;
    case TEAMS:
        strcpy(info.team_uuid, client->team_uuid);
        strcpy(info.channel_uuid, client->channel_uuid);
        break;
    case CHANNEL:
        strcpy(info.team_uuid, client->team_uuid);
        strcpy(info.channel_uuid, client->channel_uuid);
        strcpy(info.thread_uuid, client->thread_uuid);
        break;
    }
    write(client->socket_fd, &info, sizeof(cli_create_t));
    return (INFO);
}

int c_info(char *buff, client_t *client)
{
    message_t msg;
    cli_create_t info;

    memset(&info, 0, sizeof(cli_create_t));
    memset(info.thread_uuid, 0, MAX_NAME_LENGTH);
    memset(info.team_uuid, 0, MAX_NAME_LENGTH);
    memset(info.channel_uuid, 0, MAX_NAME_LENGTH);
    memset(info.description, 0, MAX_DESCRIPTION_LENGTH);
    memset(info.name, 0, MAX_NAME_LENGTH);
    memset(info.comment_body, 0, MAX_BODY_LENGTH);
    if (not_logged(client) == 0)
        return (0);
    if (buff[0] != '\n')
        return (CMD_ERROR);
    msg.command = INFO;
    write(client->socket_fd, &msg, sizeof(message_t));
    return (copy_right_uuids(client, info));
}