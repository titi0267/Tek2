/*
** EPITECH PROJECT, 2022
** teams
** File description:
** info
*/

#include "../../include/teams.h"
#include "../../include/command.h"

static int copy_right_uuids(client_t *client, cli_info_t info)
{
    info.use_arg = client->use_status;
    switch (info.use_arg)
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
    write(client->socket_fd, &info, sizeof(cli_info_t));
    return (INFO);
}

int c_info(char *buff, client_t *client)
{
    message_t msg;
    cli_info_t info;

    if (not_logged(client) == 0)
        return (0);
    if (buff[0] != '\n')
        return (CMD_ERROR);
    msg.command = INFO;
    write(client->socket_fd, &msg, sizeof(message_t));
    return (copy_right_uuids(client, info));
}