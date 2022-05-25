/*
** EPITECH PROJECT, 2022
** teams
** File description:
** login
*/

#include "../../include/teams.h"
#include "../../../include/communication.h"

void write_first_user(client_list_t *client, cli_login_t login, int fd)
{
    server_user_t new_user = {login.name, "1"};

    write(fd, &new_user, sizeof(server_user_t));
    server_event_user_logged_in(new_user.uid);
    client->pseudo = new_user.pseudo;
    client->uid = new_user.uid;
}

void write_user(client_list_t *client, cli_login_t login, int fd)
{
    server_user_t tmp = {login.name, ""};
    int read_ret = 0;

        read_ret = read(fd, &tmp, sizeof(server_user_t));
    while ((read_ret = read(fd, &tmp, sizeof(server_user_t))) != 0
    && read_ret != -1) {
        if (strcmp(tmp.pseudo, login.name) == 0) {
            client->pseudo = tmp.pseudo;
            client->uid = tmp.uid;
            server_event_user_logged_in(tmp.uid);
            return;
        }
    }
    if (strcmp(tmp.uid, "") == 0)
        return(write_first_user(client, login, fd));
    tmp.uid = increment_str(tmp.uid);
    write(fd, &tmp, sizeof(server_user_t));
    server_event_user_logged_in(tmp.uid);
    client->pseudo = tmp.pseudo;
    client->uid = tmp.uid;
}

void login(client_list_t *client)
{
    cli_login_t login;
    int does_save_file_exist = 0;
    int fd = 0;

    does_save_file_exist = open("./saves/users.txt", O_RDONLY);
    fd = open("./saves/users.txt", O_RDWR | O_APPEND | O_CREAT);
    read(client->fd, &login, sizeof(cli_login_t));
    if (!does_save_file_exist)
        return(write_first_user(client, login, fd));
    return(write_user(client, login, fd));
}