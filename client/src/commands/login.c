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
    int i = 0;

    memset(login.name, 0, MAX_NAME_LENGTH);
    if (check_is_arg(buff) == CMD_ERROR ||
        check_valid_cmd_type(buff) == CMD_ERROR)
        return (CMD_ERROR);
    buff += 2;
    printf("Login with ");
    for (; i < strlen(buff) - 2; i++)
        login.name[i] = buff[i];
    login.name[i] = '\0';
    printf("%s\n", login.name);
    msg.command = LOGIN;
    write(client->socket_fd, &msg, (sizeof(message_t)));
    write(client->socket_fd, &login, sizeof(cli_login_t));
    //client_event_logged_in()
    return (LOGIN);
}