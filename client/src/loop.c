/*
** EPITECH PROJECT, 2022
** teams
** File description:
** loop
*/

#include "../include/teams.h"

void loop(client_t *client)
{
    char *buff = malloc(BUFFER_SIZE);

    memset(buff, 0, BUFFER_SIZE);
    while (strcmp(buff, "/logout") != 0) {
        printf("%s> ", client->log_status == LOGGED ? client->pseudo : "");
        if (scanf("%s", buff) == EOF)
            break;
        printf("%s\n", buff);
    }
    free_all(client, buff);
}