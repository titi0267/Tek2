/*
** EPITECH PROJECT, 2022
** teams
** File description:
** print_allusers
*/

#include "../../include/teams.h"

void print_all_user(void)
{
    int fd = 0;
    int read_ret = 0;
    server_user_t tmp;

    fd = open("./saves/users.txt", O_RDONLY);
    if (fd == -1)
        return;
    while ((read_ret = read(fd, &tmp, sizeof(server_user_t))) != 0
    && read_ret != -1)
        server_event_user_loaded(tmp.pseudo, tmp.uid);
}