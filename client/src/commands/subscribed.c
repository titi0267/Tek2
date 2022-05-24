/*
** EPITECH PROJECT, 2022
** teams
** File description:
** subscribed
*/

#include "../../include/command.h"

int c_subscribed(char *buff)
{
    if (buff[0] != '\n' && (check_is_arg(buff) == CMD_ERROR ||
        check_valid_cmd_type(buff) == CMD_ERROR ||
        check_valid_uuid(buff) == CMD_ERROR))
        return (CMD_ERROR);
    printf("subscribed\n");
    return (SUBSCRIBED);
}