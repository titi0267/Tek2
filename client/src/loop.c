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
    int command = -1;
    message_t *msg = malloc(sizeof(message_t));

    msg->command = 16;
    while (command != LOGOUT) {
        printf("%s > ", client->log_status == LOGGED ? client->pseudo : "");
        if (getline(&buff, &n, stdin) == -1)
            break;
        command = parse_cmd(buff);
        write(client->socket_fd, msg, sizeof(message_t));
    }
    free(msg);
    free_all(client, buff);
}