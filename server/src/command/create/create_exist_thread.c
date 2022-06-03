/*
** EPITECH PROJECT, 2022
** teams
** File description:
** create_exist_thread
*/

#include "../../../include/teams.h"

int thread_check_loop(struct dirent *ep, char *team_uid, char *channel_uid,
char *new_name)
{
    int fd = 0;
    char *path = malloc(100);
    server_create_info_t info;

    if (strncmp(ep->d_name, "th_", 3) == 0) {
        sprintf(path, "./saves/teams/t_%d/c_%d/%s/thread_info.txt",
        atoi(team_uid), atoi(channel_uid), ep->d_name);
        fd = open(path, O_RDONLY);
        if (fd == -1)
            return (1);
        read(fd, &info, sizeof(server_create_info_t));
        if (strcmp(info.name, new_name) == 0)
            return (1);
    }
    return (0);
}

int thread_name_already_exist(char *team_uid, char *channel_uid,
char *new_team_name)
{
    char *path = malloc(100);
    DIR *dir;
    struct dirent *ep;

    sprintf(path, "./saves/teams/t_%d/c_%d", atoi(team_uid), atoi(channel_uid));
    dir = opendir(path);
    if (!dir)
        return (1);
    while ((ep = readdir(dir))) {
        if (thread_check_loop(ep, team_uid, channel_uid, new_team_name))
            return (1);
    }
    return (0);
}