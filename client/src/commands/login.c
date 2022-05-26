/*
** EPITECH PROJECT, 2022
** teams
** File description:
** login
*/

#include "../../include/teams.h"
#include "../../include/command.h"

void server_answer(client_t *client, cli_login_t login)
{
    server_user_t user;

    read(client->socket_fd, &user, sizeof(server_user_t));
    strcpy(client->user_uuid, user.uid);
    strcpy(client->pseudo, user.pseudo);
    client->log_status = LOGGED;
    client_event_logged_in(client->user_uuid, client->pseudo);
}

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
    server_answer(client, login);
    return (LOGIN);
}