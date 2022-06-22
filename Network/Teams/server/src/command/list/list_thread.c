/*
** EPITECH PROJECT, 2022
** teams
** File description:
** list_thread
*/

#include "../../../include/teams.h"

void send_thread_info(client_list_t *client, cli_create_t payload,
struct dirent *ep)
{
    char path[500];
    int fd = 0;
    server_create_info_t thread;

    sprintf(path, "./saves/teams/t_%d/c_%d/%s/thread_info.txt",
    atoi(payload.team_uuid), atoi(payload.channel_uuid), ep->d_name);
    fd = open(path, O_RDONLY);
    if (fd == -1)
        return;
    read(fd, &thread, sizeof(server_create_info_t));
    write(client->fd, &thread, sizeof(server_create_info_t));
}

void list_thread(client_list_t *client, cli_create_t payload)
{
    char path[100];
    DIR *dir;
    struct dirent *ep;
    message_t message = {LIST};

    sprintf(path, "./saves/teams/t_%d/c_%d", atoi(payload.team_uuid)
    , atoi(payload.channel_uuid));
    dir = opendir(path);
    if (!dir)
        return (ret_thread_error(client, payload,
        get_thread_error_level(payload)));
    if (!is_subscribed(payload.team_uuid, client->uid))
        return (ret_thread_error(client, payload, UNAUTHORIZED));
    write(client->fd, &message, sizeof(message_t));
    while ((ep = readdir(dir))) {
        if (strncmp(ep->d_name, "th_", 3) == 0)
            send_thread_info(client, payload, ep);
    }
    send_last_item(client);
}