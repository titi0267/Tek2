/*
** EPITECH PROJECT, 2022
** teams
** File description:
** login
*/

#include "../../include/teams.h"
#include "../../include/reply.h"
#include "../../include/command.h"

int r_login(client_t *client)
{
    server_user_t user;

    read(client->socket_fd, &user, sizeof(server_user_t));
    strcpy(client->user_uuid, user.uid);
    strcpy(client->pseudo, user.pseudo);
    client->log_status = LOGGED;
    client_event_logged_in(client->user_uuid, client->pseudo);
}