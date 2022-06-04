/*
** EPITECH PROJECT, 2022
** teams
** File description:
** list
*/

#include "../../include/teams.h"
#include "../../include/command.h"

static int copy_right_uuids(client_t *client, cli_create_t list)
{
    list.args_nbr = client->use_status;
    switch (list.args_nbr)
    {
    case TEAMS:
        strcpy(list.team_uuid, client->team_uuid);
        break;
    case CHANNEL:
        strcpy(list.team_uuid, client->team_uuid);
        strcpy(list.channel_uuid, client->channel_uuid);
        break;
    case THREADS:
        strcpy(list.team_uuid, client->team_uuid);
        strcpy(list.channel_uuid, client->channel_uuid);
        strcpy(list.thread_uuid, client->thread_uuid);
        break;
    }
    write(client->socket_fd, &list, sizeof(cli_create_t));
    return (LIST);
}

int c_list(char *buff, client_t *client)
{
    message_t msg;
    cli_create_t list;

    memset(&list, 0, sizeof(cli_create_t));
    memset(list.thread_uuid, 0, MAX_NAME_LENGTH);
    memset(list.team_uuid, 0, MAX_NAME_LENGTH);
    memset(list.channel_uuid, 0, MAX_NAME_LENGTH);
    memset(list.description, 0, MAX_DESCRIPTION_LENGTH);
    memset(list.name, 0, MAX_NAME_LENGTH);
    memset(list.comment_body, 0, MAX_BODY_LENGTH);
    if (not_logged(client) == 0)
        return (0);
    if (buff[0] != '\n')
        return (CMD_ERROR);
    msg.command = LIST;
    write(client->socket_fd, &msg, sizeof(message_t));
    return (copy_right_uuids(client, list));
}