/*
** EPITECH PROJECT, 2022
** teams
** File description:
** info_channel
*/

#include "../../../include/teams.h"

void info_channel(client_list_t *client, cli_create_t payload)
{
    char path[100];
    int fd = 0;
    message_t message = {INFO};
    server_create_info_t channel;

    sprintf(path, "./saves/teams/t_%d/c_%d/channel_info.txt",
    atoi(payload.team_uuid), atoi(payload.channel_uuid));
    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (ret_thread_error(client, payload,
        get_thread_error_level(payload)));
    if (!is_subscribed(payload.team_uuid, client->uid))
        return (ret_thread_error(client, payload, UNAUTHORIZED));
    read(fd, &channel, sizeof(server_create_info_t));
    write(client->fd, &message, sizeof(message_t));
    write(client->fd, &channel, sizeof(server_create_info_t));
}