/*
** EPITECH PROJECT, 2022
** teams
** File description:
** subribe
*/

#include "../../include/teams.h"
#include "../../include/command.h"

int c_subscribe(char *buff, client_t *client)
{
    message_t msg;
    cli_subscribe_t cli_sub;

    memset(cli_sub.team_uuid, 0, MAX_NAME_LENGTH);
    if (not_logged(client) == 0)
        return (0);
    if (check_is_arg(buff) == CMD_ERROR || check_valid_cmd_type(buff)
        == CMD_ERROR || check_valid_uuid(buff) == CMD_ERROR)
        return (CMD_ERROR);
    buff += 2;
    printf("Subscribe to ");
    for (size_t i = 0; i < strlen(buff) - 2; i++)
        cli_sub.team_uuid[i] = buff[i];
    printf("%s\n", cli_sub.team_uuid);
    msg.command = SUBSCRIBE;
    write(client->socket_fd, &msg, sizeof(message_t));
    write(client->socket_fd, &cli_sub, sizeof(cli_subscribe_t));
    return (SUBSCRIBE);
}