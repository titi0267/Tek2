/*
** EPITECH PROJECT, 2022
** teams
** File description:
** login
*/

#include "../../include/teams.h"
#include "../../include/reply.h"
#include "../../include/command.h"

void r_login(client_t *client)
{
    server_user_t user;

    memset(user.uid, 0, MAX_NAME_LENGTH);
    memset(user.pseudo, 0, MAX_NAME_LENGTH);
    read(client->socket_fd, &user, sizeof(server_user_t));
    if (strcmp(user.pseudo, client->tmp_login) == 0) {
        strcpy(client->user_uuid, user.uid);
        strcpy(client->pseudo, user.pseudo);
        client->log_status = LOGGED;
    }
    client_event_logged_in(user.uid, user.pseudo);
}