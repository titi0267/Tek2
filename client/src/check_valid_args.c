/*
** EPITECH PROJECT, 2022
** teams
** File description:
** check_valid_args
*/

#include "../include/command.h"

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
    for (int i = 1; i < strlen(buff) - 2; i++) {
        if (buff[i] < 48 || buff[i] > 57)
            return (CMD_ERROR);
    }
    return (0);
}
