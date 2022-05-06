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
    message_t *msg = malloc(sizeof(message_t));

    msg->command = -1;
    while (msg->command != LOGOUT) {
        printf("%s > ", client->log_status == LOGGED ? client->pseudo : "");
        if (getline(&buff, &n, stdin) == -1)
            break;
        msg->command = parse_cmd(buff);
        write(client->socket_fd, msg, sizeof(message_t));
    }
    free(msg);
    free_all(client, buff);
}