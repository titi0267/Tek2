/*
** EPITECH PROJECT, 2022
** teams
** File description:
** list_channel
*/

#include "../../../include/teams.h"

void send_channel_info(client_list_t *client, cli_create_t payload,
struct dirent *ep)
{
    char path[500];
    int fd = 0;
    server_create_info_t channel;

    sprintf(path, "./saves/teams/t_%d/%s/channel_info.txt",
    atoi(payload.team_uuid),ep->d_name);
    fd = open(path, O_RDONLY);
    if (fd == -1)
        return;
    read(fd, &channel, sizeof(server_create_info_t));
    write(client->fd, &channel, sizeof(server_create_info_t));
}

void list_channel(client_list_t *client, cli_create_t payload)
{
    char path[100];
    DIR *dir;
    struct dirent *ep;
    message_t message = {LIST};

    sprintf(path, "./saves/teams/t_%d", atoi(payload.team_uuid));
    dir = opendir(path);
    if (!dir)
        return (ret_channel_error(client, payload, TEAM_ERROR));
    if (!is_subscribed(payload.team_uuid, client->uid))
        return (ret_channel_error(client, payload, UNAUTHORIZED));
    write(client->fd, &message, sizeof(message_t));
    while ((ep = readdir(dir))) {
        if (strncmp(ep->d_name, "c_", 2) == 0)
            send_channel_info(client, payload, ep);
    }
    send_last_item(client);
}