/*
** EPITECH PROJECT, 2022
** teams
** File description:
** login
*/

#include "../../include/teams.h"
#include "../../../include/communication.h"

server_user_t get_default_user()
{
    server_user_t tmp;

    memset(tmp.pseudo, 0, MAX_NAME_LENGTH);
    memset(tmp.uid, 0, MAX_NAME_LENGTH);
    return (tmp);
}

void write_first_user(client_list_t *client, cli_login_t login, int fd)
{
    server_user_t new_user = get_default_user();

    strcpy(new_user.pseudo, login.name);
    strcpy(new_user.uid, "1");
    write(fd, &new_user, sizeof(server_user_t));
    write(client->fd, &new_user, sizeof(server_user_t));
    server_event_user_created(new_user.uid, new_user.pseudo);
    client->uid = strdup(new_user.uid);
    client->pseudo = strdup(new_user.pseudo);
}

int check_if_user_exist(client_list_t *client, cli_login_t login, int fd)
{
    server_user_t tmp = get_default_user();
    int read_ret = 0;
    int last_id = -1;

    while ((read_ret = read(fd, &tmp, sizeof(server_user_t))) != 0
    && read_ret != -1) {
        if (strcmp(tmp.pseudo, login.name) == 0) {
            client->uid = strdup(tmp.uid);
            client->pseudo = strdup(tmp.pseudo);
            server_event_user_logged_in(tmp.uid);
            write(client->fd, &tmp, sizeof(server_user_t));
            return (-2);
        }
        last_id = atoi(tmp.uid);
    }
    return (last_id);
}

void write_user(client_list_t *client, cli_login_t login, int fd)
{
    server_user_t tmp = get_default_user();
    int last_id = -3;

    last_id = check_if_user_exist(client, login, fd);
    if (last_id == -2)
        return;
    if (last_id == -1)
        return(write_first_user(client, login, fd));
    strcpy(tmp.uid, increment_str(last_id));
    strcpy(tmp.pseudo, login.name);
    write(fd, &tmp, sizeof(server_user_t));
    write(client->fd, &tmp, sizeof(server_user_t));
    server_event_user_created(tmp.uid, tmp.pseudo);
    client->uid = strdup(tmp.uid);
    client->pseudo = strdup(tmp.pseudo);
}

void login(teams_t *server, client_list_t *client)
{
    cli_login_t login;
    int does_save_file_exist = 0;
    int fd = 0;

    UNUSED(server);
    does_save_file_exist = open("./saves/users.txt", O_RDONLY);
    fd = open("./saves/users.txt", O_RDWR | O_APPEND | O_CREAT, 0777);
    read(client->fd, &login, sizeof(cli_login_t));
    if (!does_save_file_exist)
        return (write_first_user(client, login, fd));
    return (write_user(client, login, fd));
}