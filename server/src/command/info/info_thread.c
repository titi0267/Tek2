/*
** EPITECH PROJECT, 2022
** teams
** File description:
** info_thread
*/

#include "../../../include/teams.h"

void info_thread(client_list_t *client, cli_create_t payload)
{
    char path[100];
    int fd = 0;
    message_t message = {INFO};
    server_create_info_t thread;

    sprintf(path, "./saves/teams/t_%d/c_%d/th_%d/thread_info.txt",
    atoi(payload.team_uuid), atoi(payload.channel_uuid),
    atoi(payload.thread_uuid));
    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (ret_reply_error(client, payload,
        get_reply_error_level(payload)));
    if (!is_subscribed(payload.team_uuid, client->uid))
        return (ret_reply_error(client, payload, UNAUTHORIZED));
    read(fd, &thread, sizeof(server_create_info_t));
    write(client->fd, &message, sizeof(message_t));
    write(client->fd, &thread, sizeof(server_create_info_t));
}