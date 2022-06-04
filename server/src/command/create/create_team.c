/*
** EPITECH PROJECT, 2022
** teams
** File description:
** create_team
*/

#include "../../../include/teams.h"
#include <time.h>

void send_team_error(client_list_t *client,
cli_create_t payload)
{
    server_create_info_t team_info = get_create_info_struct();
    message_t message = {CREATE};

    team_info.error = TEAM_NAME_ALREADY_TAKEN;
    team_info.create_type = DEFAULT;
    team_info.time = time(NULL);
    strcpy(team_info.name, payload.name);
    strcpy(team_info.description, payload.description);
    strcpy(team_info.creator_uuid, client->uid);
    write(client->fd, &message, sizeof(message_t));
    write(client->fd, &team_info, sizeof(server_create_info_t));
}

server_create_info_t create_team_info(client_list_t *client,
cli_create_t payload, char *id)
{
    server_create_info_t team_info = get_create_info_struct();

    team_info.error = NO_ERROR;
    team_info.create_type = DEFAULT;
    team_info.time = time(NULL);
    strcpy(team_info.name, payload.name);
    strcpy(team_info.team_uuid, id);
    strcpy(team_info.description, payload.description);
    strcpy(team_info.creator_uuid, client->uid);
    return (team_info);
}

void create_first_team(teams_t *server,
client_list_t *client, cli_create_t payload)
{
    int fd = 0;
    server_create_info_t team_info;

    mkdir("./saves/teams/t_1", 0777);
    fd = open("./saves/teams/t_1/team_info.txt", O_RDWR | O_CREAT, 0777);
    if (fd == -1)
        return;
    team_info = create_team_info(client, payload, "1");
    write(fd, &team_info, sizeof(server_create_info_t));
    send_to_everyone_logged(server, (int)CREATE,
    &team_info, sizeof(server_create_info_t));
    server_event_team_created(team_info.team_uuid,
    team_info.name, client->uid);
}

void create_next_team(client_list_t *client, teams_t *server,
cli_create_t payload, char *last_id)
{
    char *path = malloc(100);
    server_create_info_t team_info;
    int fd = 0;

    sprintf(path, "./saves/teams/t_%d", atoi(last_id) + 1);
    mkdir(path, 0777);
    sprintf(path, "./saves/teams/t_%d/team_info.txt",
    atoi(last_id) + 1);
    fd = open(path, O_RDWR | O_CREAT, 0777);
    if (fd == -1)
        return;
    team_info = create_team_info(client,
    payload, increment_str(atoi(last_id)));
    write(fd, &team_info, sizeof(server_create_info_t));
    send_to_everyone_logged(server, (int)CREATE,
    &team_info, sizeof(server_create_info_t));
    server_event_team_created(team_info.team_uuid,
    team_info.name, client->uid);
}

void create_team(teams_t *server, client_list_t *client, cli_create_t payload)
{
    struct dirent *ep;
    DIR *dir = opendir("./saves/teams");
    char *buff = "";

    if (team_name_already_exist(payload.name))
        return (send_team_error(client, payload));
    while ((ep = readdir(dir))) {
        if (strncmp(ep->d_name, "t_", 2) == 0 &&
        is_bigger_id(ep->d_name, buff))
            buff = ep->d_name;
    }
    if (strlen(buff) == 0)
        return (create_first_team(server, client, payload));
    buff += 2;
    create_next_team(client, server, payload, buff);
}