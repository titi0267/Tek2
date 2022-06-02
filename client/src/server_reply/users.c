/*
** EPITECH PROJECT, 2022
** teams
** File description:
** users
*/

#include "../../include/teams.h"
#include "../../include/reply.h"
#include "../../include/command.h"

void r_users(client_t *client)
{
    server_get_user_t user;

    while (1) {
        read(client->socket_fd, &user, sizeof(server_get_user_t));
        if (user.found == NOT_FOUND)
            break;
        client_print_users(user.uid, user.pseudo, user.connected);
    }
}