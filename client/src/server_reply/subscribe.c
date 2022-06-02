/*
** EPITECH PROJECT, 2022
** teams
** File description:
** subscribe
*/

#include "../../include/teams.h"
#include "../../include/reply.h"
#include "../../include/command.h"

void r_subscribe(client_t *client)
{
    server_sub_t sub;

    read(client->socket_fd, &sub, sizeof(server_sub_t));
    //client_print_subscribed(sub.)
    UNUSED(client);
}