/*
** EPITECH PROJECT, 2022
** teams
** File description:
** loop
*/

#include "../include/teams.h"

void loop(client_t *client)
{
    char *buff = NULL;
    size_t n = 0;
    int command = 0;

    while (command != LOGOUT) {
        printf("%s > ", client->log_status == LOGGED ? client->pseudo : "");
        if (getline(&buff, &n, stdin) == -1)
            break;
        command = parse_cmd(buff, client);
        if (command == 84)
            printf("Error: Invalid Command\n");
    }
    free_all(client, buff);
}