/*
** EPITECH PROJECT, 2022
** teams
** File description:
** send
*/

#include "../../include/teams.h"
#include "../../include/command.h"

int send_to_serv(char *buff, client_t *client, cli_send_t cli_send)
{
    message_t msg;

    msg.command = SEND;
    write(client->socket_fd, &msg, sizeof(message_t));
    for (int i = 0; buff[i] != '"'; i++) {
        cli_send.body[i] = buff[i];
        if (i > MAX_BODY_LENGTH || buff[i] == '\n') {
            return (CMD_ERROR);
        }
    }
    printf("Send to %s : ", cli_send.user_uuid);
    printf("%s\n", cli_send.body);
    write(client->socket_fd, &cli_send, sizeof(cli_send_t));
    return (SEND);
}

int c_send(char *buff, client_t *client)
{
    cli_send_t cli_send;
    int i = 0;

    memset(cli_send.body, 0, MAX_BODY_LENGTH);
    memset(cli_send.user_uuid, 0, MAX_NAME_LENGTH);
    if (check_is_arg(buff) == CMD_ERROR)
        return (CMD_ERROR);
    buff += 2;
    for (; buff[i] != '"'; i++) {
        cli_send.user_uuid[i] = buff[i];
        if (buff[i] < 48 || buff[i] > 57 || i > MAX_NAME_LENGTH)
            return (CMD_ERROR);
    }
    buff += i;
    if (buff[0] != '"' || check_is_arg(buff + 1) == CMD_ERROR)
        return (CMD_ERROR);
    buff += 3;
    return (send_to_serv(buff, client, cli_send));
}