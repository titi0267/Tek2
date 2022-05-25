/*
** EPITECH PROJECT, 2022
** teams
** File description:
** create
*/

#include "../../include/teams.h"
#include "../../include/command.h"

int create_fill_body(char *buff, client_t *client, cli_create_t *create)
{
    for (int i = 0; buff[i] != '"'; i++) {
        create->comment_body[i] = buff[i];
        if (buff[i] == '\n' || i > MAX_BODY_LENGTH)
            return (CMD_ERROR);
    }
    write(client->socket_fd, create, sizeof(cli_create_t));
    printf("create : %s\n", create->comment_body);
    return (CREATE);
}

int c_create(char *buff, client_t *client)
{
    message_t msg;
    cli_create_t *create = malloc(sizeof(cli_create_t));

    memset(create->comment_body, 0, MAX_BODY_LENGTH);
    memset(create->team_uuid, 0, MAX_NAME_LENGTH);
    if (check_is_arg(buff) == CMD_ERROR) {
        free(create);
        return (CMD_ERROR);
    }
    buff += 2;
    msg.command = CREATE;
    write(client->socket_fd, &msg, sizeof(message_t));
    //need server answer to check if args are valid
    return (create_fill_body(buff, client, create));
}