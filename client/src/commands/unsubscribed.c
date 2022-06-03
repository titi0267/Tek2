/*
** EPITECH PROJECT, 2022
** teams
** File description:
** unsubscribed
*/

#include "../../include/teams.h"
#include "../../include/command.h"

int c_unsubscribe(char *buff, client_t *client)
{
    message_t msg;
    cli_unsubscribe_t unsub;

    memset(unsub.team_uuid, 0, MAX_NAME_LENGTH);
    if (not_logged(client) == 0)
        return (0);
    if (check_is_arg(buff) == CMD_ERROR || check_valid_cmd_type(buff)
        == CMD_ERROR || check_valid_uuid(buff) == CMD_ERROR)
        return (CMD_ERROR);
    buff += 2;
    for (size_t i = 0; i < strlen(buff) - 2; i++)
        unsub.team_uuid[i] = buff[i];
    msg.command = UNSUBSCRIBE;
    write(client->socket_fd, &msg, sizeof(message_t));
    write(client->socket_fd, &unsub, sizeof(cli_unsubscribe_t));
    return (UNSUBSCRIBE);
}