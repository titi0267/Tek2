/*
** EPITECH PROJECT, 2022
** teams
** File description:
** subscribe
*/

#include "../../include/teams.h"
#include <sys/types.h>
#include <dirent.h>

// TO USE LATER
// void create_team(client_list_t *client, cli_subscribe_t subscribe_payload)
// {
//     char *path = malloc(MAX_NAME_LENGTH);
//     DIR *dir;

//     printf("%s\n", subscribe_payload.team_uuid);
//     sprintf(path, "./saves/teams/t_%s", subscribe_payload.team_uuid);
//     dir = opendir(path);
//     if (dir)
//         return;
//     free(path);
//     mkdir(path, 777);
// }

server_team_user_t get_team_user(char *pseudo, char *uid)
{
    server_team_user_t team_user;

    team_user.is_active = 1;
    memset(team_user.pseudo, 0, MAX_NAME_LENGTH);
    strcpy(team_user.pseudo, pseudo);
    memset(team_user.uid, 0, MAX_NAME_LENGTH);
    strcpy(team_user.uid, uid);
}

int get_open_team_users(client_list_t *client,
cli_subscribe_t subscribe_payload)
{
    char *path = malloc(MAX_NAME_LENGTH);
    int fd = 0;

    sprintf(path, "./saves/teams/t_%s/users.txt", subscribe_payload.team_uuid);
    fd = open(path, O_RDWR | O_CREAT);
    free(path);
    return (fd);
}

int check_inactive_user(client_list_t *client, int fd)
{
    server_team_user_t tmp;
    int read_ret = 0;

    while ((read_ret = read(fd, &tmp, sizeof(server_team_user_t))) != 0
    && read_ret != -1) {
        if (tmp.is_active == 0) {
            lseek(fd, -sizeof(server_team_user_t), SEEK_CUR);
            tmp = get_team_user(client->pseudo, client->uid);
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
    int fd = 0;

    subscribe_res.exist == 0;
    read(client->fd, &subscribe_payload, sizeof(cli_subscribe_t));
    fd = get_open_team_users(client, subscribe_payload);
    if (fd == -1)
        write(client->fd, &subscribe_res, sizeof(server_sub_t));
    subscribe_res.exist = 1;
    if (check_inactive_user(client, fd))
        return;
    tmp = get_team_user(client->pseudo, client->uid);
    lseek(fd, 0, SEEK_END);
    write(fd, &tmp, sizeof(server_team_user_t));
    write(client->fd, &subscribe_res, sizeof(server_sub_t));
}