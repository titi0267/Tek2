/*
** EPITECH PROJECT, 2022
** teams
** File description:
** user
*/

#include "../../include/teams.h"
#include "../../include/command.h"

int c_user(char *buff, client_t *client)
{
    message_t msg;
    cli_users_t usrs;

    memset(usrs.user_uuid, 0, MAX_NAME_LENGTH);
    if (not_logged(client) == 0)
        return (0);
    if (check_is_arg(buff) == CMD_ERROR ||
        check_valid_cmd_type(buff) == CMD_ERROR ||
        check_valid_uuid(buff) == CMD_ERROR)
        return (CMD_ERROR);
    buff += 2;
    for (size_t i = 0; i < strlen(buff) - 2; i++)
        usrs.user_uuid[i] = buff[i];
    msg.command = USER;
    write(client->socket_fd, &msg, sizeof(message_t));
    write(client->socket_fd, &usrs, sizeof(cli_users_t));
    return (USER);
}