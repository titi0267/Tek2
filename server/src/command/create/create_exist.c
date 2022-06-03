/*
** EPITECH PROJECT, 2022
** teams
** File description:
** create_exist
*/

#include "../../../include/teams.h"

int team_check_loop(struct dirent *ep, char *new_team_name)
{
    int fd = 0;
    char *path = malloc(100);
    server_create_info_t info;

    if (strncmp(ep->d_name, "t_", 2) == 0) {
        sprintf(path, "./saves/teams/%s/team_info.txt", ep->d_name);
        fd = open(path, O_RDONLY);
        if (fd == -1)
            return (1);
        read(fd, &info, sizeof(server_create_info_t));
        if (strcmp(info.name, new_team_name) == 0)
            return (1);
    }
    return (0);
}

int team_name_already_exist(char *new_team_name)
{
    char *path = malloc(100);
    DIR *dir;
    struct dirent *ep;

    sprintf(path, "./saves/teams");
    dir = opendir(path);
    if (!dir)
        return (1);
    while ((ep = readdir(dir))) {
        if (team_check_loop(ep, new_team_name))
            return (1);
    }
    return (0);
}

int channel_check_loop(struct dirent *ep, char *team_uid, char *new_name)
{
    int fd = 0;
    char *path = malloc(100);
    server_create_info_t info;

    if (strncmp(ep->d_name, "c_", 2) == 0) {
        sprintf(path, "./saves/teams/t_%d/%s/channel_info.txt", atoi(team_uid),
        ep->d_name);
        fd = open(path, O_RDONLY);
        if (fd == -1)
            return (1);
        read(fd, &info, sizeof(server_create_info_t));
        if (strcmp(info.name, new_name) == 0)
            return (1);
    }
    return (0);
}

int channel_name_already_exist(char *team_uid, char *new_team_name)
{
    char *path = malloc(100);
    DIR *dir;
    struct dirent *ep;

    sprintf(path, "./saves/teams/t_%d", atoi(team_uid));
    dir = opendir(path);
    if (!dir)
        return (1);
    while ((ep = readdir(dir))) {
        if (channel_check_loop(ep, team_uid, new_team_name))
            return (1);
    }
    return (0);
}