/*
** EPITECH PROJECT, 2022
** teams
** File description:
** subscribed_utils
*/

#include "../../include/teams.h"

void send_last_subscribed_user(client_list_t *client)
{
    server_subscribed_info_t last;

    memset(&last, 0, sizeof(last));
    last.last = 1;
    last.error = 0;
    last.is_user = 1;
    last.connected = 0;
    memset(last.name, 0, MAX_NAME_LENGTH);
    memset(last.id, 0, MAX_NAME_LENGTH);
    memset(last.description, 0, MAX_DESCRIPTION_LENGTH);
    write(client->fd, &last, sizeof(server_subscribed_info_t));
}

void send_subscribed_error(client_list_t *client)
{
    server_subscribed_info_t error;
    message_t command = {SUBSCRIBED};

    memset(&error, 0, sizeof(error));
    error.error = 1;
    error.last = 1;
    error.is_user = 1;
    error.connected = 0;
    memset(error.name, 0, MAX_NAME_LENGTH);
    memset(error.id, 0, MAX_NAME_LENGTH);
    memset(error.description, 0, MAX_DESCRIPTION_LENGTH);
    write(client->fd, &command, sizeof(message_t));
    write(client->fd, &error, sizeof(server_subscribed_info_t));
}

void send_user_as_subscribed_payload(teams_t *server, client_list_t *client,
server_team_user_t team_user)
{
    server_subscribed_info_t sub_payload;

    memset(&sub_payload, 0, sizeof(server_subscribed_info_t));
    sub_payload.error = 0;
    sub_payload.last = 0;
    sub_payload.is_user = 1;
    sub_payload.connected = is_connected(server, team_user.uid);
    memset(sub_payload.name, 0, MAX_NAME_LENGTH);
    memset(sub_payload.id, 0, MAX_NAME_LENGTH);
    memset(sub_payload.description, 0, MAX_DESCRIPTION_LENGTH);
    strcpy(sub_payload.name, team_user.pseudo);
    strcpy(sub_payload.id, team_user.uid);
    write(client->fd, &sub_payload, sizeof(server_subscribed_info_t));
}

void send_team_as_subscribed_payload(client_list_t *client,
server_create_info_t team_info)
{
    server_subscribed_info_t sub_payload;

    memset(&sub_payload, 0, sizeof(server_subscribed_info_t));
    sub_payload.error = 0;
    sub_payload.last = 0;
    sub_payload.is_user = 1;
    sub_payload.connected = 0;
    memset(sub_payload.name, 0, MAX_NAME_LENGTH);
    memset(sub_payload.id, 0, MAX_NAME_LENGTH);
    memset(sub_payload.description, 0, MAX_DESCRIPTION_LENGTH);
    strcpy(sub_payload.name, team_info.name);
    strcpy(sub_payload.id, team_info.team_uuid);
    strcpy(sub_payload.description, team_info.description);
    write(client->fd, &sub_payload, sizeof(server_subscribed_info_t));
}

int is_subscribed(char *team_id, char *uid)
{
    char *path = malloc(100);
    server_team_user_t tmp;
    int read_ret = 0;
    int fd = 0;

    sprintf(path, "./saves/teams/t_%d/users.txt", atoi(team_id));
    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (0);
    while ((read_ret = read(fd, &tmp, sizeof(server_team_user_t))) != 0
    && read_ret != -1) {
        if (tmp.is_active && strcmp(tmp.uid, uid) == 0)
            return (1);
    }
    return (0);
}