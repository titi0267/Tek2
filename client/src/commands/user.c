/*
** EPITECH PROJECT, 2022
** teams
** File description:
** user
*/

#include "../../include/teams.h"
#include "../../include/command.h"

int c_user(char *buff, client_t *client)
{
    if (check_is_arg(buff) == CMD_ERROR ||
        check_valid_cmd_type(buff) == CMD_ERROR)
        return (CMD_ERROR);
    buff++;
    for (int i = 0; i < strlen(buff) - 2; i++)
        printf("%c", buff[i]);
    puts("");
    return (USER);
}