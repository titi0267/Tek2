/*
** EPITECH PROJECT, 2022
** teams
** File description:
** logout
*/

#include "../../include/teams.h"

void logout(teams_t *server, client_list_t *client)
{
    cli_logout_t logout;
    server_user_t user = get_default_user();

    read(client->fd, &logout, sizeof(cli_logout_t));
    if (strlen(client->uid) != 0) {
        strcpy(user.pseudo, client->pseudo);
        strcpy(user.uid, client->uid);
        send_to_everyone(server, (int)LOGOUT, &user, sizeof(server_user_t));
        server_event_user_logged_out(client->uid);
    }
}