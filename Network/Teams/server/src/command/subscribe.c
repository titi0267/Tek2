/*
** EPITECH PROJECT, 2022
** teams
** File description:
** subscribe
*/

#include "../../include/teams.h"
#include <sys/types.h>
#include <dirent.h>

server_sub_t get_sub_res(client_list_t *client,
cli_subscribe_t subscribe_payload)
{
    server_sub_t sub;

    memset(&sub, 0, sizeof(sub));
    sub.exist = 1;
    memset(sub.team_uid, 0, MAX_NAME_LENGTH);
    memset(sub.user_uuid, 0, MAX_NAME_LENGTH);
    strcpy(sub.team_uid, subscribe_payload.team_uuid);
    strcpy(sub.user_uuid, client->uid);
    return (sub);
}

server_team_user_t get_team_user(char *pseudo, char *uid)
{
    server_team_user_t team_user;

    memset(&team_user, 0, sizeof(team_user));
    team_user.is_active = 1;
    memset(team_user.pseudo, 0, MAX_NAME_LENGTH);
    strcpy(team_user.pseudo, pseudo);
    memset(team_user.uid, 0, MAX_NAME_LENGTH);
    strcpy(team_user.uid, uid);
    return (team_user);
}

int get_open_team_users(cli_subscribe_t subscribe_payload)
{
    char *path = malloc(100);
    int fd = 0;

    sprintf(path, "./saves/teams/t_%d/users.txt",
    atoi(subscribe_payload.team_uuid));
    fd = open(path, O_RDWR | O_CREAT, 0777);
    free(path);
    return (fd);
}

int check_inactive_user(client_list_t *client,
cli_subscribe_t subscribe_payload,int fd)
{
    server_team_user_t tmp;
    int read_ret = 0;

    while ((read_ret = read(fd, &tmp, sizeof(server_team_user_t))) != 0
    && read_ret != -1) {
        if (tmp.is_active == 0) {
            lseek(fd, -sizeof(server_team_user_t), SEEK_CUR);
            tmp = get_team_user(client->pseudo, client->uid);
            server_event_user_subscribed(subscribe_payload.team_uuid,
            client->uid);
            write(fd, &tmp, sizeof(server_team_user_t));
            return (1);
        }
    }
    return (0);
}

void subscribe(teams_t *server, client_list_t *client)
{
    cli_subscribe_t subscribe_payload;
    server_team_user_t tmp;
    server_sub_t subscribe_res;
    message_t command = {SUBSCRIBE};
    int fd = 0;

    UNUSED(server);
    read(client->fd, &subscribe_payload, sizeof(cli_subscribe_t));
    fd = get_open_team_users(subscribe_payload);
    if (fd == -1)
        return (send_sub_error(client));
    if (!check_inactive_user(client, subscribe_payload, fd)) {
        tmp = get_team_user(client->pseudo, client->uid);
        lseek(fd, 0, SEEK_END);
        server_event_user_subscribed(subscribe_payload.team_uuid, client->uid);
        write(fd, &tmp, sizeof(server_team_user_t));
    }
    subscribe_res = get_sub_res(client, subscribe_payload);
    write(client->fd, &command, sizeof(message_t));
    write(client->fd, &subscribe_res, sizeof(server_sub_t));
}