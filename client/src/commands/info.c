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
    cli_info_t info;

    if (not_logged(client) == 0)
        return (0);
    if (buff[0] != '\n')
        return (CMD_ERROR);
    printf("info based on what /use defined earlier\n");
    msg.command = INFO;
    write(client->socket_fd, &msg, sizeof(message_t));
    info.use_arg = client->use_status;
    write(client->socket_fd, &info, sizeof(cli_info_t));
    return (INFO);
}