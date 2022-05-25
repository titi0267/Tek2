/*
** EPITECH PROJECT, 2022
** teams
** File description:
** list
*/

#include "../../include/teams.h"
#include "../../include/command.h"

int c_list(char *buff, client_t *client)
{
    message_t msg;

    if (buff[0] != '\n')
        return (CMD_ERROR);
    printf("list based on what /use defined earlier\n");
    msg.command = LIST;
    write(client->socket_fd, &msg, sizeof(message_t));
    return (LIST);
}