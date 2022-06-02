/*
** EPITECH PROJECT, 2022
** teams
** File description:
** subscribed
*/

#include "../../include/teams.h"

void check_if_user_in_team(client_list_t *client, struct dirent *ep)
{
    int fd = 0;
    server_create_info_t team_info;
    char *tmp = "";
    char *path = malloc(100);

    if (strncmp(ep->d_name, "t_", 2) == 0) {
        tmp = ep->d_name;
        tmp += 2;
        if (is_subscribed(tmp, client->uid)) {
            sprintf(path, "./saves/teams/t_%d/team_info.txt", atoi(tmp));
            fd = open(path, O_RDONLY);
            read(fd, &team_info, sizeof(server_create_info_t));
            send_team_as_subscribed_payload(client, team_info);
        }
    }
}

void list_all_my_teams(client_list_t *client)
{
    DIR *dir;
    char *path = malloc(100);
    message_t message;
    struct dirent *ep;

    message.command = SUBSCRIBED;
    sprintf(path, "./saves/teams");
    dir = opendir(path);
    if (!dir)
        return (send_subscribed_error(client));
    write(client->fd, &message, sizeof(message_t));
    while ((ep = readdir(dir)))
        check_if_user_in_team(client, ep);
    send_last_subscribed_user(client);
}

void list_user_in_team(teams_t *server, client_list_t *client,
cli_subscribed_t req)
{
    char *path = malloc(100);
    server_team_user_t tmp;
    message_t message;
    int read_ret = 0;
    int fd = 0;

    message.command = SUBSCRIBED;
    sprintf(path, "./saves/teams/t_%d/users.txt", atoi(req.team_uuid));
    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (send_subscribed_error(client));
    write(client->fd, &message, sizeof(message_t));
    while ((read_ret = read(fd, &tmp, sizeof(server_team_user_t))) != 0
    && read_ret != -1) {
        if (tmp.is_active)
            send_user_as_subscribed_payload(server, client, tmp);
    }
    send_last_subscribed_user(client);
}

void subscribed_command(teams_t *server, client_list_t *client)
{
    cli_subscribed_t req;

    read(client->fd, &req, sizeof(cli_subscribed_t));
    if (strlen(req.team_uuid) == 0)
        return (list_all_my_teams(client));
    list_user_in_team(server, client, req);
}