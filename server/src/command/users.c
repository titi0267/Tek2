/*
** EPITECH PROJECT, 2022
** teams
** File description:
** users
*/

#include "../../include/teams.h"

void users(teams_t *server, client_list_t *client)
{
    server_get_user_t user = default_get_user();
    server_user_t tmp = get_default_user();
    int read_ret = 0;
    int fd = 0;

    fd = open("./saves/users.txt", O_RDWR | O_APPEND | O_CREAT);
    while ((read_ret = read(fd, &tmp, sizeof(server_user_t))) != 0
    && read_ret != -1) {
        user.found = FOUND;
        user.found = isConnected(server, tmp.uid);
        strcpy(user.pseudo, tmp.pseudo);
        strcpy(user.uid, tmp.uid);
        write(client->fd, &user, sizeof(server_get_user_t));
    }
    user = default_get_user();
    write(client->fd, &user, sizeof(server_get_user_t));
}
