/*
** EPITECH PROJECT, 2022
** teams
** File description:
** list_team
*/

#include "../../../include/teams.h"

void send_team_info(client_list_t *client, struct dirent *ep)
{
    char path[500];
    int fd = 0;
    server_create_info_t team;

    sprintf(path, "./saves/teams/%s/team_info.txt", ep->d_name);
    fd = open(path, O_RDONLY);
    if (fd == -1)
        return;
    read(fd, &team, sizeof(server_create_info_t));
    write(client->fd, &team, sizeof(server_create_info_t));
}

void list_team(client_list_t *client, cli_create_t payload)
{
    char path[100];
    DIR *dir;
    struct dirent *ep;
    message_t message = {LIST};

    UNUSED(payload);
    sprintf(path, "./saves/teams");
    dir = opendir(path);
    if (!dir)
        return;
    write(client->fd, &message, sizeof(message_t));
    while ((ep = readdir(dir))) {
        if (strncmp(ep->d_name, "t_", 2) == 0)
            send_team_info(client, ep);
    }
    send_last_item(client);
}