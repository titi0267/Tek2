/*
** EPITECH PROJECT, 2022
** teams
** File description:
** list_reply
*/

#include "../../../include/teams.h"

void send_reply_list(client_list_t *client, cli_create_t payload)
{
    char path[100];
    int fd = 0;
    server_create_info_t info;
    int read_ret = 0;

    sprintf(path, "./saves/teams/t_%d/c_%d/th_%d/reply.txt",
    atoi(payload.team_uuid), atoi(payload.channel_uuid),
    atoi(payload.thread_uuid));
    fd = open(path, O_RDONLY);
    if (fd == -1)
        return;
    while ((read_ret = read(fd, &info, sizeof(server_team_user_t))) != 0
    && read_ret != -1)
        write(client->fd, &info, sizeof(server_create_info_t));
}

void list_reply(client_list_t *client, cli_create_t payload)
{
    char path[100];
    DIR *dir;
    message_t message = {LIST};

    sprintf(path, "./saves/teams/t_%d/c_%d/th_%d", atoi(payload.team_uuid)
    , atoi(payload.channel_uuid), atoi(payload.thread_uuid));
    dir = opendir(path);
    if (!dir)
        return (ret_reply_error(client, payload,
        get_thread_error_level(payload)));
    if (!is_subscribed(payload.team_uuid, client->uid))
        return (ret_reply_error(client, payload, UNAUTHORIZED));
    write(client->fd, &message, sizeof(message_t));
    send_reply_list(client, payload);
    send_last_item(client);
}