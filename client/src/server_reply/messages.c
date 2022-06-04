/*
** EPITECH PROJECT, 2022
** teams
** File description:
** messages
*/

#include "../../include/teams.h"
#include "../../include/reply.h"
#include "../../include/command.h"

void r_messages(client_t *client)
{
    server_message_t serv_msg;

    while (1) {
        read(client->socket_fd, &serv_msg, sizeof(server_message_t));
        if (serv_msg.is_valid == 0)
            break;
        if (serv_msg.is_valid == -1) {
            client_error_unknown_user(serv_msg.to);
            break;
        }
        client_private_message_print_messages(serv_msg.from,
            serv_msg.time, serv_msg.body);
    }
}