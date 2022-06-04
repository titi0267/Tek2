/*
** EPITECH PROJECT, 2022
** teams
** File description:
** info_team
*/

#include "../../../include/teams.h"

void info_team(client_list_t *client, cli_create_t payload)
{
    char path[100];
    int fd = 0;
    message_t message = {INFO};
    server_create_info_t team;

    sprintf(path, "./saves/teams/t_%d/team_info.txt", atoi(payload.team_uuid));
    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (ret_channel_error(client, payload, TEAM_ERROR));
    if (!is_subscribed(payload.team_uuid, client->uid))
        return (ret_channel_error(client, payload, UNAUTHORIZED));
    read(fd, &team, sizeof(server_create_info_t));
    write(client->fd, &message, sizeof(message_t));
    write(client->fd, &team, sizeof(server_create_info_t));
}