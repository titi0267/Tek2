/*
** EPITECH PROJECT, 2022
** teams
** File description:
** create_chanel
*/

#include "../../../include/teams.h"
#include <time.h>

void ret_channel_error(client_list_t *client, cli_create_t payload,
int error_code)
{
    server_create_info_t chanel_info = get_create_info_struct();
    message_t message = {CREATE};

    strcpy(chanel_info.name, payload.name);
    strcpy(chanel_info.team_uuid, payload.team_uuid);
    strcpy(chanel_info.description, payload.description);
    strcpy(chanel_info.creator_uuid, client->uid);
    chanel_info.create_type = TEAMS;
    chanel_info.error = error_code;
    chanel_info.time = time(NULL);
    write(client->fd, &message, sizeof(message_t));
    write(client->fd, &chanel_info, sizeof(server_create_info_t));
}

server_create_info_t create_chanel_info(client_list_t *client,
cli_create_t payload, char *id)
{
    server_create_info_t chanel_info = get_create_info_struct();

    chanel_info.error = NO_ERROR;
    chanel_info.create_type = TEAMS;
    chanel_info.time = time(NULL);
    strcpy(chanel_info.name, payload.name);
    strcpy(chanel_info.team_uuid, payload.team_uuid);
    strcpy(chanel_info.description, payload.description);
    strcpy(chanel_info.channel_uuid, id);
    strcpy(chanel_info.creator_uuid, client->uid);
    return (chanel_info);
}

void create_first_chanel(teams_t *server, client_list_t *client,
cli_create_t payload)
{
    int fd = 0;
    server_create_info_t chanel_info;
    char *path = malloc(100);

    sprintf(path, "./saves/teams/t_%d/c_1", atoi(payload.team_uuid));
    mkdir(path, 0777);
    sprintf(path, "./saves/teams/t_%d/c_1/channel_info.txt",
    atoi(payload.team_uuid));
    fd = open(path, O_RDWR | O_CREAT, 0777);
    if (fd == -1)
        return;
    chanel_info = create_chanel_info(client, payload, "1");
    write(fd, &chanel_info, sizeof(server_create_info_t));
    send_to_team(server, &chanel_info, sizeof(server_create_info_t),
    chanel_info.team_uuid);
    server_event_channel_created(chanel_info.team_uuid,
    chanel_info.channel_uuid, chanel_info.name);
}

void create_next_chanel(teams_t *server, client_list_t *cli,
cli_create_t req, char *last_id)
{
    char *path = malloc(100);
    server_create_info_t chanel_info;
    int fd = 0;

    sprintf(path, "./saves/teams/t_%d/c_%d", atoi(req.team_uuid)
    , atoi(last_id) + 1);
    mkdir(path, 0777);
    sprintf(path, "./saves/teams/t_%d/c_%d/channel_info.txt"
    , atoi(req.team_uuid), atoi(last_id) + 1);
    fd = open(path, O_RDWR | O_CREAT, 0777);
    if (fd == -1)
        return;
    chanel_info = create_chanel_info(cli, req, increment_str(atoi(last_id)));
    write(fd, &chanel_info, sizeof(server_create_info_t));
    send_to_team(server, &chanel_info, sizeof(server_create_info_t),
    chanel_info.team_uuid);
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
        return (ret_channel_error(client, payload, TEAM_ERROR));
    if (!is_subscribed(payload.team_uuid, client->uid))
        return (ret_channel_error(client, payload, UNAUTHORIZED));
    if (channel_name_already_exist(payload.team_uuid, payload.name))
        return (ret_channel_error(client, payload,
        CHANNEL_NAME_ALREADY_TAKEN));
    while ((ep = readdir(dir)))
        (strncmp(ep->d_name, "c_", 2) == 0 && is_bigger_id(ep->d_name, buff))
        ?  buff = ep->d_name : 0;
    if (strlen(buff++) == 0)
        return (create_first_chanel(server, client, payload));
    create_next_chanel(server, client, payload, ++buff);
}