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
    message_t *msg = malloc(sizeof(message_t));

    memset(buff, 0, BUFFER_SIZE);
    msg->command = 16;
    while (strcmp(buff, "/logout") != 0) {
        printf("%s > ", client->log_status == LOGGED ? client->pseudo : "");
        if (scanf("%s", buff) == EOF)
            break;
        write(client->socket_fd, msg, sizeof(message_t));
    }
    free_all(client, buff);
}