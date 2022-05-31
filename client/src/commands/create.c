/*
** EPITECH PROJECT, 2022
** teams
** File description:
** create
*/

#include "../../include/teams.h"
#include "../../include/command.h"

int check_create_args(char *buff)
{
    int sz = 0;

    if (check_is_arg(buff) == CMD_ERROR)
        return (CMD_ERROR);
    buff += 2;
    if ((sz = check_valid_length(buff, MAX_NAME_LENGTH)) == -1)
        return (CMD_ERROR);
    return (sz);
}

int create_uuid(char *buff, client_t *client, cli_create_t *create)
{
    int sz = 0;
    int i = 0;

    if ((sz = check_create_args(buff)) == CMD_ERROR)
        return (CMD_ERROR);
    buff += 2;
    for (i = 0; i < sz; i++)
        create->name[i] = buff[i];
    buff += (i + 1);
    if ((sz = check_create_args(buff)) == CMD_ERROR)
        return (CMD_ERROR);
    buff += 2;
    for (i = 0; i < sz; i++)
        create->description[i] = buff[i];
    buff += (i + 1);
    if (buff[0] != '\n')
        return (CMD_ERROR);
    return (CREATE);
}

int create_thread(char *buff, client_t *client, cli_create_t *create)
{
    int i = 0;

    for (; buff[i] != '"' && buff[i] != 0; i++) {
        create->comment_body[i] = buff[i];
        if (buff[i] == '\n' || i > MAX_BODY_LENGTH)
            return (CMD_ERROR);
    }
    if (buff[i] == 0 || buff[i] != '"' || buff[i + 1] != '\n')
        return (CMD_ERROR);
    return (CREATE);
}

int create_right_params(char *buff, client_t *client, cli_create_t *create)
{
    int ret_val = 0;

    if (client->use_status != THREADS)
        ret_val = create_uuid(buff, client, create);
    else
        ret_val = create_thread(buff, client, create);
    if (ret_val == CMD_ERROR)
        return (ret_val);
    strcpy(create->team_uuid, client->team_uuid);
    strcpy(create->channel_uuid, client->channel_uuid);
    strcpy(create->thread_uuid, client->thread_uuid);
    create->args_nbr = client->use_status;
    printf("[%s : %s] | [%s]\nUse %i : [%s] | [%s] | [%s]\n", create->name, create->description, create->comment_body, create->args_nbr, create->team_uuid, create->channel_uuid, create->thread_uuid);
    write(client->socket_fd, create, sizeof(cli_create_t));
    return (CREATE);
}

int c_create(char *buff, client_t *client)
{
    message_t msg;
    cli_create_t create;

    memset(create.comment_body, 0, MAX_BODY_LENGTH);
    memset(create.name, 0, MAX_NAME_LENGTH);
    memset(create.description, 0, MAX_NAME_LENGTH);
    create.args_nbr = DEFAULT;
    if (not_logged(client) == 0)
        return (0);
    msg.command = CREATE;
    write(client->socket_fd, &msg, sizeof(message_t));
    return (create_right_params(buff, client, &create));
}