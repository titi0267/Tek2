/*
** EPITECH PROJECT, 2022
** teams
** File description:
** logout
*/

#include "../../include/teams.h"
#include "../../include/command.h"

int c_logout(char *buff, client_t *client)
{
    cli_logout_t logout;
    message_t msg;

    logout.logout = 1;
    msg.command = LOGOUT;
    if (buff[0] != '\n')
        return (CMD_ERROR);
    write(client->socket_fd, &msg, sizeof(message_t));
    write(client->socket_fd, &logout, sizeof(cli_logout_t));
    return (LOGOUT);
}