/*
** EPITECH PROJECT, 2022
** teams
** File description:
** create_team
*/

#include "../../../include/teams.h"

void failed_to_create_team(client_list_t *client, cli_create_t payload)
{
    
}

void create_first_team(client_list_t *client, cli_create_t payload)
{
    int fd = 0;

    mkdir("./saves/teams/t_1", 0777);
    fd = open("./saves/teams/t_1/team_info.txt", O_RDWR | O_CREAT, 0777);
    if (fd == -1)
        return;
    
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
    if(strlen(buff) == 0)
        create_first_team(client, payload);
    //sprintf(path, "./saves/teams/t_%s", payload.team_uuid);
    //dir = opendir("./saves");
    // if (dir)
    //     return;
    //free(path);
    //mkdir(path, 777);
}