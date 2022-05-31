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
    cli_list_t list;

    if (not_logged(client) == 0)
        return (0);
    if (buff[0] != '\n')
        return (CMD_ERROR);
    printf("list based on what /use defined earlier\n");
    msg.command = LIST;
    write(client->socket_fd, &msg, sizeof(message_t));
    list.use_arg = client->use_status;
    write(client->socket_fd, &list, sizeof(cli_list_t));
    return (LIST);
}