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

    if (check_is_arg(buff) == CMD_ERROR ||
        check_valid_cmd_type(buff) == CMD_ERROR)
        return (CMD_ERROR);
    buff += 2;
    printf("Login with ");
    for (int i = 0; i < strlen(buff) - 2; i++) {
        login.name[i] = buff[i];
        printf("%c", buff[i]);
    }
    puts("");
    msg.command = LOGIN;
    write(client->socket_fd, &msg, (sizeof(message_t)));
    write(client->socket_fd, &login, sizeof(cli_login_t));
    return (LOGIN);
}