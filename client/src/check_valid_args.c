/*
** EPITECH PROJECT, 2022
** teams
** File description:
** check_valid_args
*/

#include "../include/teams.h"

int check_is_arg(char *buff)
{
    if (buff[0] != ' ' || buff[1] != '"')
        return (CMD_ERROR);
    return (0);
}

int check_valid_cmd_type(char *buff)
{
    buff += 2;
    if (buff[strlen(buff) - 1] != '\n' ||
        buff[strlen(buff) - 2] != '"' ||
        (strlen(buff) - 2) > MAX_NAME_LENGTH || (strlen(buff) - 2) == 0)
        return (CMD_ERROR);
    return (0);
}

int check_valid_uuid(char *buff)
{
    buff++;
    for (size_t i = 1; i < strlen(buff) - 2; i++) {
        if (buff[i] < 48 || buff[i] > 57)
            return (CMD_ERROR);
    }
    return (0);
}

int check_valid_length(char *buff, int max_sz)
{
    int i = 0;

    for (; buff[i] != '"' && buff[i] != 0; i++)
        if (i > max_sz)
            return (-1);
    if (buff[i] == 0 || i == 0)
        return (-1);
    return (i);
}

int not_logged(client_t *client)
{
    if (client->log_status == NOT_LOGGED) {
        client_error_unauthorized();
        return (0);
    }
    return (-1);
}