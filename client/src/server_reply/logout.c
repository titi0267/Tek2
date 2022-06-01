/*
** EPITECH PROJECT, 2022
** teams
** File description:
** logout
*/

#include "../../include/teams.h"
#include "../../include/reply.h"
#include "../../include/command.h"

int r_logout(client_t *client)
{
    server_user_t usr_logout;

    read(client->socket_fd, &usr_logout, sizeof(server_user_t));
    if (client->user_uuid[0] != 0)
        client_event_logged_out(usr_logout.uid, usr_logout.pseudo);
}