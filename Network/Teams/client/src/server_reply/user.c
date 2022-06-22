/*
** EPITECH PROJECT, 2022
** teams
** File description:
** user
*/

#include "../../include/teams.h"
#include "../../include/reply.h"
#include "../../include/command.h"

void r_user(client_t *client)
{
    server_get_user_t user;

    read(client->socket_fd, &user, sizeof(server_get_user_t));
    if (user.found == NOT_FOUND) {
        client_error_unknown_user(user.uid);
        return;
    }
    client_print_user(user.uid, user.pseudo, user.connected);
}