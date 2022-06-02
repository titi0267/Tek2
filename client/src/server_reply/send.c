/*
** EPITECH PROJECT, 2022
** teams
** File description:
** send
*/

#include "../../include/teams.h"
#include "../../include/reply.h"
#include "../../include/command.h"

void r_send(client_t *client)
{
    server_message_t srv_msg;

    read(client->socket_fd, &srv_msg, sizeof(server_message_t));
    if (srv_msg.is_valid == 0) {
        client_error_unknown_user(srv_msg.to);
        return;
    }
    client_event_private_message_received(srv_msg.from, srv_msg.body);
}