/*
** EPITECH PROJECT, 2022
** teams
** File description:
** logout
*/

#include "../../include/teams.h"
#include "../../include/reply.h"
#include "../../include/command.h"

void r_logout(client_t *client)
{
    server_user_t usr_logout;

    read(client->socket_fd, &usr_logout, sizeof(server_user_t));
    client_event_logged_out(usr_logout.uid, usr_logout.pseudo);
    if (strcmp(client->user_uuid, usr_logout.uid) == 0)
        client->logout = 2;
}