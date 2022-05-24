/*
** EPITECH PROJECT, 2022
** teams
** File description:
** login
*/

#include "../../include/teams.h"
int c_login(char *buff)
{
    if (check_is_arg(buff) == CMD_ERROR ||
        check_valid_cmd_type(buff) == CMD_ERROR)
        return (CMD_ERROR);
    buff += 2;
    printf("Login with ");
    for (int i = 0; i < strlen(buff) - 2; i++)
    printf("%c", buff[i]);
    puts("");
    return (LOGIN);
}