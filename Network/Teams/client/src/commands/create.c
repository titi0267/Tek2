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

int create_uuid(char *buff, cli_create_t *create)
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

int create_thread(char *buff, cli_create_t *create)
{
    int i = 0;

    if (check_is_arg(buff) == CMD_ERROR)
        return (CMD_ERROR);
    buff += 2;
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
    message_t msg;

    if (client->use_status != THREADS)
        ret_val = create_uuid(buff, create);
    else
        ret_val = create_thread(buff, create);
    if (ret_val == CMD_ERROR)
        return (ret_val);
    strcpy(create->team_uuid, client->team_uuid);
    strcpy(create->channel_uuid, client->channel_uuid);
    strcpy(create->thread_uuid, client->thread_uuid);
    msg.command = CREATE;
    write(client->socket_fd, &msg, sizeof(message_t));
    create->args_nbr = client->use_status;
    write(client->socket_fd, create, sizeof(cli_create_t));
    return (CREATE);
}

int c_create(char *buff, client_t *client)
{
    cli_create_t create;

    memset(&create, 0, sizeof(cli_create_t));
    memset(create.comment_body, 0, MAX_BODY_LENGTH);
    memset(create.name, 0, MAX_NAME_LENGTH);
    memset(create.description, 0, MAX_DESCRIPTION_LENGTH);
    memset(create.channel_uuid, 0, MAX_NAME_LENGTH);
    memset(create.thread_uuid, 0, MAX_NAME_LENGTH);
    memset(create.team_uuid, 0, MAX_NAME_LENGTH);
    create.args_nbr = DEFAULT;
    if (not_logged(client) == 0)
        return (0);
    return (create_right_params(buff, client, &create));
}