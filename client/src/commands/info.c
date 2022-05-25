/*
** EPITECH PROJECT, 2022
** teams
** File description:
** info
*/

#include "../../include/teams.h"
#include "../../include/command.h"

int c_info(char *buff, client_t *client)
{
    message_t msg;

    if (buff[0] != '\n')
        return (CMD_ERROR);
    printf("info based on what /use defined earlier\n");
    msg.command = INFO;
    write(client->socket_fd, &msg, sizeof(message_t));
    return (INFO);
}