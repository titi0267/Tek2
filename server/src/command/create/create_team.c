/*
** EPITECH PROJECT, 2022
** teams
** File description:
** create_team
*/

#include "../../../include/teams.h"

void create_team(teams_t *server, client_list_t *client, cli_create_t payload)
{
    char *path = malloc(MAX_NAME_LENGTH);
    DIR *dir;

    sprintf(path, "./saves/teams/t_%s", payload.team_uuid);
    dir = opendir("./saves");
    if (dir)
        return;
    free(path);
    mkdir(path, 777);
}