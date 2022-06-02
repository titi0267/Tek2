/*
** EPITECH PROJECT, 2022
** teams
** File description:
** list
*/

#include "../../include/teams.h"
#include "../../include/command.h"

static int copy_right_uuids(client_t *client, cli_list_t list)
{
    list.use_arg = client->use_status;
    switch (list.use_arg)
    {
    case DEFAULT:
        strcpy(list.team_uuid, client->team_uuid);
        break;
    case TEAMS:
        strcpy(list.team_uuid, client->team_uuid);
        strcpy(list.channel_uuid, client->channel_uuid);
        break;
    case CHANNEL:
        strcpy(list.team_uuid, client->team_uuid);
        strcpy(list.channel_uuid, client->channel_uuid);
        strcpy(list.thread_uuid, client->thread_uuid);
        break;
    }
    write(client->socket_fd, &list, sizeof(cli_list_t));
    return (LIST);
}

int c_list(char *buff, client_t *client)
{
    message_t msg;
    cli_list_t list;

    memset(list.thread_uuid, 0, MAX_NAME_LENGTH);
    memset(list.team_uuid, 0, MAX_NAME_LENGTH);
    memset(list.channel_uuid, 0, MAX_NAME_LENGTH);
    if (not_logged(client) == 0)
        return (0);
    if (buff[0] != '\n')
        return (CMD_ERROR);
    msg.command = LIST;
    write(client->socket_fd, &msg, sizeof(message_t));
    return (copy_right_uuids(client, list));
}