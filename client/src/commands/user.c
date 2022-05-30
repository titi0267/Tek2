/*
** EPITECH PROJECT, 2022
** teams
** File description:
** user
*/

#include "../../include/teams.h"
#include "../../include/command.h"

void get_user(client_t *client)
{
    server_get_user_t user;

    read(client->socket_fd, &user, sizeof(server_get_user_t));
    client_print_user(user.uid, user.pseudo, user.connected);
}

int c_user(char *buff, client_t *client)
{
    message_t msg;
    cli_users_t usrs;

    memset(usrs.user_uuid, 0, MAX_NAME_LENGTH);
    if (client->log_status == NOT_LOGGED || check_is_arg(buff) == CMD_ERROR ||
        check_valid_cmd_type(buff) == CMD_ERROR ||
        check_valid_uuid(buff) == CMD_ERROR)
        return (CMD_ERROR);
    buff += 2;
    for (int i = 0; i < strlen(buff) - 2; i++)
        usrs.user_uuid[i] = buff[i];
    msg.command = USER;
    write(client->socket_fd, &msg, sizeof(message_t));
    write(client->socket_fd, &usrs, sizeof(cli_users_t));
    get_user(client);
    return (USER);
}