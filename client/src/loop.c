/*
** EPITECH PROJECT, 2022
** teams
** File description:
** loop
*/

#include "../include/teams.h"

static void clear_fds(client_t *client)
{
    FD_ZERO(&client->client_rd);
    FD_SET(client->socket_fd, &client->client_rd);
    FD_SET(0, &client->client_rd);
}

int parse_recv(client_t *client)
{
    printf("recieved\n");
}

int get_cmd(client_t *client, char *buff)
{
    int command = 0;
    size_t n = 0;
    message_t msg;

    memset(buff, 0, 1024);
    if (FD_ISSET(client->socket_fd, &client->client_rd)) {
        if (read(client->socket_fd, &msg, sizeof(message_t)) == 0)
            return (-1);
        get_server_recv(client, msg);
        if (client->log_status == LOGGED)
            write(1, client->pseudo, MAX_NAME_LENGTH);
        write(1, " > ", 3);

    }
    if (FD_ISSET(0, &client->client_rd)) {
        if (read(0, buff, 1024) == 0)
            return (-1);
        command = parse_cmd(buff, client);
        if (command == 84)
            printf("Error: Invalid Command\n");
        if (client->log_status == LOGGED)
            write(1, client->pseudo, MAX_NAME_LENGTH);
        write(1, " > ", 3);
    }
    return (command);
}

void loop(client_t *client)
{
    int command = 0;
    char *buff = malloc(sizeof(char) * 1024);
    int ret_sel = 0;

    memset(client->user_uuid, 0, MAX_NAME_LENGTH);
    memset(client->tmp_login, 0, MAX_NAME_LENGTH);
    //printf("%s > ", client->log_status == LOGGED ? client->pseudo : "");
    if (client->log_status == LOGGED)
        write(1, client->pseudo, MAX_NAME_LENGTH);
    write(1, " > ", 3);
    while (command != LOGOUT) {
        clear_fds(client);
        ret_sel =
        select(FD_SETSIZE, &client->client_rd, NULL, NULL, NULL);
        if (ret_sel >= 0)
            command = get_cmd(client, buff);
        if (command == -1)
            break;
    }
    free_all(client, buff);
}