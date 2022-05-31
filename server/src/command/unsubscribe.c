/*
** EPITECH PROJECT, 2022
** teams
** File description:
** unsubscribe
*/

#include "../../include/teams.h"

int get_open_team_users_unsub(client_list_t *client,
cli_unsubscribe_t unsubscribe_payload)
{
    char *path = malloc(MAX_NAME_LENGTH);
    int fd = 0;

    sprintf(path, "./saves/teams/t_%s/users.txt",
    unsubscribe_payload.team_uuid);
    fd = open(path, O_RDWR | O_CREAT, 0777);
    free(path);
    return (fd);
}

int unsub_user(client_list_t *client, cli_unsubscribe_t unsub_payload, int fd)
{
    int read_ret = 0;
    server_team_user_t tmp;
    server_sub_t res_payload;

    res_payload.exist = 1;
    while ((read_ret = read(fd, &tmp, sizeof(server_team_user_t))) != 0
    && read_ret != -1) {
        if (strcmp(tmp.uid, client->uid) == 0) {
            lseek(fd, -sizeof(server_team_user_t), SEEK_CUR);
            tmp.is_active = 0;
            write(fd, &tmp, sizeof(server_team_user_t));
            write(client->fd, &res_payload, sizeof(server_sub_t));
            return (1);
        }
    }
    return (0);
}

void unsubscribe(teams_t *server, client_list_t *client)
{
    cli_unsubscribe_t unsub_payload;
    server_sub_t res_payload;
    int fd = 0;

    UNUSED(server);
    res_payload.exist = 0;
    read(client->fd, &unsub_payload, sizeof(cli_unsubscribe_t));
    fd = get_open_team_users_unsub(client, unsub_payload);
    if (fd == -1) {
        write(client->fd, &res_payload, sizeof(server_sub_t));
        return;
    }
    if (unsub_user(client, unsub_payload, fd))
        return;
    write(client->fd, &res_payload, sizeof(server_sub_t));
}