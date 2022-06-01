/*
** EPITECH PROJECT, 2022
** teams
** File description:
** create_team
*/

#include "../../../include/teams.h"

server_team_info_t create_team_info(cli_create_t payload, char *id)
{
    server_team_info_t team_info;

    team_info.is_valid = 1;
    memset(team_info.name, 0, MAX_NAME_LENGTH);
    memset(team_info.team_uuid, 0, MAX_NAME_LENGTH);
    memset(team_info.description, 0, MAX_DESCRIPTION_LENGTH);
    strcpy(team_info.name, payload.name);
    strcpy(team_info.team_uuid, id);
    strcpy(team_info.description, payload.description);
    return (team_info);
}

void create_first_team(client_list_t *client, cli_create_t payload)
{
    int fd = 0;
    server_team_info_t team_info;

    mkdir("./saves/teams/t_1", 0777);
    fd = open("./saves/teams/t_1/team_info.txt", O_RDWR | O_CREAT, 0777);
    if (fd == -1)
        return;
    team_info = create_team_info(payload, "1");
    write(fd, &team_info, sizeof(server_team_info_t));
    write(client->fd, &team_info, sizeof(server_team_info_t));
    server_event_team_created(team_info.team_uuid,
    team_info.name, client->uid);
}

void create_next_team(client_list_t *client,
cli_create_t payload, char *last_id)
{
    char *path = malloc(MAX_NAME_LENGTH);
    server_team_info_t team_info;
    int fd = 0;

    printf("%s\n", increment_str(atoi(last_id)));
    sprintf(path, "./saves/teams/t_%d", atoi(last_id) + 1);
    mkdir(path, 0777);
    sprintf(path, "./saves/teams/t_%d/team_info.txt",
    atoi(last_id) + 1);
    fd = open(path, O_RDWR | O_CREAT, 0777);
    if (fd == -1)
        return;
    team_info = create_team_info(payload, increment_str(atoi(last_id)));
    write(fd, &team_info, sizeof(server_team_info_t));
    write(client->fd, &team_info, sizeof(server_team_info_t));
    server_event_team_created(team_info.team_uuid,
    team_info.name, client->uid);
}

void create_team(client_list_t *client, cli_create_t payload)
{
    struct dirent *ep;
    DIR *dir = opendir("./saves/teams");
    char *buff = "";

    while (ep = readdir(dir)) {
        if (strncmp(ep->d_name, "t_", 2) == 0)
            buff = ep->d_name;
    }
    if (strlen(buff) == 0)
        return (create_first_team(client, payload));
    buff += 2;
    create_next_team(client, payload, buff);
}