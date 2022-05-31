/*
** EPITECH PROJECT, 2022
** teams
** File description:
** users
*/

#include "../../include/teams.h"
#include "../../include/command.h"

void get_users(client_t *client)
{
    server_get_user_t user;
    int i = 1;

    while (1) {
        read(client->socket_fd, &user, sizeof(server_get_user_t));
        if (user.found == NOT_FOUND)
            break;
        client_print_users(user.uid, user.pseudo, user.connected);
    }
}

int c_users(char *buff, client_t *client)
{
    message_t msg;

    if (not_logged(client) == 0)
        return (0);
    if (buff[0] != '\n')
        return (CMD_ERROR);
    msg.command = USERS;
    write(client->socket_fd, &msg, sizeof(message_t));
    get_users(client);
    return (USERS);
}