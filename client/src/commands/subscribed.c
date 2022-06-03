/*
** EPITECH PROJECT, 2022
** teams
** File description:
** subscribed
*/

#include "../../include/teams.h"
#include "../../include/command.h"

int users_sub_to_team(char *buff, client_t *client,
    cli_subscribed_t subed, message_t msg)
{
    if (check_is_arg(buff) == CMD_ERROR)
        return (CMD_ERROR);
    buff += 2;
    for (int i = 0; buff[i] != '"'; i++) {
        subed.team_uuid[i] = buff[i];
        if (buff[i] == '\n' || i > MAX_NAME_LENGTH)
            return (CMD_ERROR);
    }
    msg.command = SUBSCRIBED;
    write(client->socket_fd, &msg, sizeof(message_t));
    write(client->socket_fd, &subed, sizeof(cli_subscribed_t));
    return (SUBSCRIBED);
}

int c_subscribed(char *buff, client_t *client)
{
    message_t msg;
    cli_subscribed_t subed;

    memset(subed.team_uuid, 0, MAX_NAME_LENGTH);
    if (not_logged(client) == 0)
        return (0);
    if (buff[0] != '\n' && (check_is_arg(buff) == CMD_ERROR ||
        check_valid_cmd_type(buff) == CMD_ERROR ||
        check_valid_uuid(buff) == CMD_ERROR))
        return (CMD_ERROR);
    if (buff[0] == '\n') {
        msg.command = SUBSCRIBED;
        write(client->socket_fd, &msg, sizeof(message_t));
        write(client->socket_fd, &subed, sizeof(cli_subscribed_t));
        return (SUBSCRIBED);
    }
    return (users_sub_to_team(buff, client, subed, msg));
}