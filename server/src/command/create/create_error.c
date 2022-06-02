/*
** EPITECH PROJECT, 2022
** teams
** File description:
** create_error
*/

#include "../../../include/teams.h"

int get_thread_error_level(cli_create_t payload)
{
    char *path = malloc(100);
    DIR *dir;

    sprintf(path, "./saves/teams/t_%d", atoi(payload.team_uuid));
    dir = opendir(path);
    if (!dir)
        return (TEAM_ERROR);
    sprintf(path, "./saves/teams/t_%d/c_%d",
    atoi(payload.team_uuid), atoi(payload.channel_uuid));
    if (!dir)
        return (CHANNEL_ERROR);
    return (NO_ERROR);
}

int get_reply_error_level(cli_create_t payload)
{
    char *path = malloc(100);
    DIR *dir;

    sprintf(path, "./saves/teams/t_%d", atoi(payload.team_uuid));
    dir = opendir(path);
    if (!dir)
        return (TEAM_ERROR);
    sprintf(path, "./saves/teams/t_%d/c_%d",
    atoi(payload.team_uuid), atoi(payload.channel_uuid));
    dir = opendir(path);
    if (!dir)
        return (CHANNEL_ERROR);
    sprintf(path, "./saves/teams/t_%d/c_%d/th_%d/reply.txt",
    atoi(payload.team_uuid), atoi(payload.channel_uuid),
    atoi(payload.thread_uuid));
    dir = opendir(path);
    if (!dir)
        return (THREAD_ERROR);
    return (NO_ERROR);
}