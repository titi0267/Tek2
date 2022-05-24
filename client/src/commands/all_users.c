/*
** EPITECH PROJECT, 2022
** teams
** File description:
** users
*/

#include "../../include/teams.h"
#include "../../include/command.h"

int c_users(char *buff, client_t *client)
{
    message_t msg;

    if (buff[0] != '\n')
        return (CMD_ERROR);
    printf("users\n");
    msg.command = USERS;
    write(client->socket_fd, &msg, sizeof(message_t));
    return (USERS);
}