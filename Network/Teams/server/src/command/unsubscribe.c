/*
** EPITECH PROJECT, 2022
** teams
** File description:
** unsubscribe
*/

#include "../../include/teams.h"

server_unsub_t get_unsub_payload(client_list_t *client,
cli_unsubscribe_t unsub_payload)
{
    server_unsub_t subscribe_res;

    memset(&subscribe_res, 0, sizeof(server_unsub_t));
    subscribe_res.valid = 1;
    memset(subscribe_res.team_uid, 0, MAX_NAME_LENGTH);
    memset(subscribe_res.user_uuid, 0, MAX_NAME_LENGTH);
    strcpy(subscribe_res.user_uuid, client->uid);
    strcpy(subscribe_res.team_uid, unsub_payload.team_uuid);
    return (subscribe_res);
}

void send_unsub_error(client_list_t *client)
{
    server_unsub_t subscribe_res;
    message_t command = {UNSUBSCRIBE};

    memset(&subscribe_res, 0, sizeof(server_unsub_t));
    subscribe_res.valid = 0;
    memset(subscribe_res.team_uid, 0, MAX_NAME_LENGTH);
    memset(subscribe_res.user_uuid, 0, MAX_NAME_LENGTH);
    write(client->fd, &command, sizeof(message_t));
    write(client->fd, &subscribe_res, sizeof(server_sub_t));
}

int get_open_team_users_unsub(cli_unsubscribe_t unsubscribe_payload)
{
    char *path = malloc(100);
    int fd = 0;

    sprintf(path, "./saves/teams/t_%d/users.txt",
    atoi(unsubscribe_payload.team_uuid));
    fd = open(path, O_RDWR | O_CREAT, 0777);
    free(path);
    return (fd);
}

int unsub_user(client_list_t *client, cli_unsubscribe_t unsub_payload, int fd)
{
    int read_ret = 0;
    server_team_user_t tmp;
    server_unsub_t res_payload;
    message_t command = {UNSUBSCRIBE};

    res_payload = get_unsub_payload(client, unsub_payload);
    while ((read_ret = read(fd, &tmp, sizeof(server_team_user_t))) != 0
    && read_ret != -1) {
        if (strcmp(tmp.uid, client->uid) == 0) {
            lseek(fd, -sizeof(server_team_user_t), SEEK_CUR);
            tmp.is_active = 0;
            server_event_user_unsubscribed(unsub_payload.team_uuid,
            client->uid);
            write(fd, &tmp, sizeof(server_team_user_t));
            write(client->fd, &command, sizeof(message_t));
            write(client->fd, &res_payload, sizeof(server_unsub_t));
            return (1);
        }
    }
    return (0);
}

void unsubscribe(teams_t *server, client_list_t *client)
{
    cli_unsubscribe_t unsub_payload;
    int fd = 0;

    UNUSED(server);
    read(client->fd, &unsub_payload, sizeof(cli_unsubscribe_t));
    fd = get_open_team_users_unsub(unsub_payload);
    if (fd == -1)
        return (send_unsub_error(client));
    if (unsub_user(client, unsub_payload, fd))
        return;
    send_unsub_error(client);
}