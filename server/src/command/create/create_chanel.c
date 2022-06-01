/*
** EPITECH PROJECT, 2022
** teams
** File description:
** create_chanel
*/

#include "../../../include/teams.h"

void ret_channel_error(client_list_t *client)
{
    server_chanel_info_t chanel_info;

    memset(&chanel_info, 0, sizeof(chanel_info));
    memset(chanel_info.name, 0, MAX_NAME_LENGTH);
    memset(chanel_info.team_uuid, 0, MAX_NAME_LENGTH);
    memset(chanel_info.description, 0, MAX_DESCRIPTION_LENGTH);
    memset(chanel_info.channel_uuid, 0, MAX_NAME_LENGTH);
    chanel_info.is_valid = 0;
    write(client->fd, &chanel_info, sizeof(server_chanel_info_t));
}

server_chanel_info_t create_chanel_info(cli_create_t payload, char *id)
{
    server_chanel_info_t chanel_info;

    memset(&chanel_info, 0, sizeof(chanel_info));
    memset(chanel_info.name, 0, MAX_NAME_LENGTH);
    memset(chanel_info.team_uuid, 0, MAX_NAME_LENGTH);
    memset(chanel_info.description, 0, MAX_DESCRIPTION_LENGTH);
    memset(chanel_info.channel_uuid, 0, MAX_NAME_LENGTH);
    chanel_info.is_valid = 1;
    strcpy(chanel_info.name, payload.name);
    strcpy(chanel_info.team_uuid, payload.team_uuid);
    strcpy(chanel_info.description, payload.description);
    strcpy(chanel_info.channel_uuid, id);
    return (chanel_info);
}

void create_first_chanel(client_list_t *client, cli_create_t payload)
{
    int fd = 0;
    server_chanel_info_t chanel_info;
    char *path = malloc(100);

    sprintf(path, "./saves/teams/t_%d/c_1", atoi(payload.team_uuid));
    mkdir(path, 0777);
    sprintf(path, "./saves/teams/t_%d/c_1/channel_info.txt",
    atoi(payload.team_uuid));
    fd = open(path, O_RDWR | O_CREAT, 0777);
    if (fd == -1)
        return;
    chanel_info = create_chanel_info(payload, "1");
    write(fd, &chanel_info, sizeof(server_chanel_info_t));
    write(client->fd, &chanel_info, sizeof(server_chanel_info_t));
    server_event_channel_created(chanel_info.team_uuid,
    chanel_info.channel_uuid, chanel_info.name);
}

void create_next_chanel(client_list_t *client,
cli_create_t payload, char *last_id)
{
    char *path = malloc(100);
    server_chanel_info_t chanel_info;
    int fd = 0;

    sprintf(path, "./saves/teams/t_%d/c_%d", atoi(payload.team_uuid)
    , atoi(last_id) + 1);
    mkdir(path, 0777);
    sprintf(path, "./saves/teams/t_%d/c_%d/channel_info.txt"
    , atoi(payload.team_uuid), atoi(last_id) + 1);
    fd = open(path, O_RDWR | O_CREAT, 0777);
    if (fd == -1)
        return;
    chanel_info = create_chanel_info(payload, increment_str(atoi(last_id)));
    write(fd, &chanel_info, sizeof(server_chanel_info_t));
    write(client->fd, &chanel_info, sizeof(server_chanel_info_t));
    server_event_team_created(chanel_info.team_uuid,
    chanel_info.name, client->uid);
    server_event_channel_created(chanel_info.team_uuid,
    chanel_info.channel_uuid, chanel_info.name);
}

void create_chanel(teams_t *server, client_list_t *client,
cli_create_t payload)
{
    struct dirent *ep;
    DIR *dir;
    char *path = malloc(MAX_NAME_LENGTH);
    char *buff = "";

    sprintf(path, "./saves/teams/t_%d", atoi(payload.team_uuid));
    dir = opendir(path);
    if (!dir)
        return (ret_channel_error(client));
    while ((ep = readdir(dir))) {
        if (strncmp(ep->d_name, "c_", 2) == 0)
            buff = ep->d_name;
    }
    if (strlen(buff) == 0)
        return (create_first_chanel(client, payload));
    buff += 2;
    create_next_chanel(client, payload, buff);
}