/*
** EPITECH PROJECT, 2022
** teams
** File description:
** exist
*/

#include "../../include/teams.h"

int user_exist(char *uid)
{
    int fd = 0;
    int read_ret = 0;
    server_user_t tmp = get_default_user();

    fd = open("./saves/users.txt", O_RDONLY);
    if (fd == -1)
        return (0);
    while ((read_ret = read(fd, &tmp, sizeof(server_user_t))) != 0
    && read_ret != -1) {
        if (strcmp(tmp.uid, uid) == 0)
            return (1);
    }
    return (0);
}