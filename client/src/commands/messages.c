/*
** EPITECH PROJECT, 2022
** teams
** File description:
** messages
*/

#include "../../include/teams.h"
#include "../../include/command.h"

int get_messages(client_t *client, cli_messages_t cli_msgs)
{
    server_message_t serv_msg;

    while (1) {
        read(client->socket_fd, &serv_msg, sizeof(server_message_t));
        if (serv_msg.is_valid == 0)
            return (MESSAGES);
        client_private_message_print_messages(serv_msg.from,
            serv_msg.time, serv_msg.body);
    }
    return (MESSAGES);
}

int c_messages(char *buff, client_t *client)
{
    message_t msg;
    cli_messages_t cli_msgs;

    if (not_logged(client) == 0)
        return (0);
    memset(cli_msgs.user_uuid, 0, MAX_NAME_LENGTH);
    if (check_is_arg(buff) == CMD_ERROR
        || check_valid_cmd_type(buff) == CMD_ERROR ||
        check_valid_uuid(buff) == CMD_ERROR)
        return (CMD_ERROR);
    buff += 2;
    for (int i = 0; i < strlen(buff) - 2; i++)
        cli_msgs.user_uuid[i] = buff[i];
    msg.command = MESSAGES;
    write(client->socket_fd, &msg, sizeof(message_t));
    write(client->socket_fd, &cli_msgs, sizeof(cli_messages_t));
    return (get_messages(client, cli_msgs));
}