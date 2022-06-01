/*
** EPITECH PROJECT, 2022
** teams
** File description:
** login
*/

#include "../../include/teams.h"
#include "../../include/command.h"

int c_login(char *buff, client_t *client)
{
    cli_login_t login;
    message_t msg;

    memset(login.name, 0, MAX_NAME_LENGTH);
    if (client->log_status == LOGGED || check_is_arg(buff) == CMD_ERROR ||
        check_valid_cmd_type(buff) == CMD_ERROR)
        return (CMD_ERROR);
    buff += 2;
    for (int i = 0; i < strlen(buff) - 2; i++)
        login.name[i] = buff[i];
    msg.command = LOGIN;
    write(client->socket_fd, &msg, (sizeof(message_t)));
    write(client->socket_fd, &login, sizeof(cli_login_t));
    strcpy(client->tmp_login, login.name);
    return (LOGIN);
}