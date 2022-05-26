/*
** EPITECH PROJECT, 2022
** teams
** File description:
** user
*/

#include "../../include/teams.h"

server_get_user_t default_get_user()
{
    server_get_user_t user;

    user.found = NOT_FOUND;
    user.connected = NOT_LOGGED;
    memset(user.uid, 0, MAX_NAME_LENGTH);
    memset(user.pseudo, 0, MAX_NAME_LENGTH);
    return (user);
}

cli_users_t get_user_to_find(client_list_t *client)
{
    cli_users_t user_to_find;

    read(client->fd, &user_to_find, sizeof(cli_users_t));
    return (user_to_find);
}

void user(teams_t *server, client_list_t *client)
{
    cli_users_t user_to_find = get_user_to_find(client);
    server_get_user_t user = default_get_user();
    server_user_t tmp = get_default_user();
    int read_ret = 0;
    int fd = 0;

    fd = open("./saves/users.txt", O_RDWR | O_APPEND | O_CREAT);
    while ((read_ret = read(fd, &tmp, sizeof(server_user_t))) != 0
    && read_ret != -1) {
        if (strcmp(tmp.uid, user_to_find.user_uuid) == 0) {
            user.found = FOUND;
            user.connected = isConnected(server, user_to_find.user_uuid);
            strcpy(user.pseudo, tmp.pseudo);
            strcpy(user.uid, tmp.uid);
            write(client->fd, &user, sizeof(server_get_user_t));
            return;
        }
    }
    user = default_get_user();
    write(client->fd, &user, sizeof(server_get_user_t));
}