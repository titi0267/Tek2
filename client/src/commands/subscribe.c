/*
** EPITECH PROJECT, 2022
** teams
** File description:
** subribe
*/

#include "../../include/teams.h"
#include "../../include/command.h"

int c_subscribe(char *buff, client_t *client)
{
    if (check_is_arg(buff) == CMD_ERROR || check_valid_cmd_type(buff)
        == CMD_ERROR || check_valid_uuid(buff) == CMD_ERROR)
        return (CMD_ERROR);
    buff += 2;
    printf("Subscribe to ");
    for (int i = 0; i < strlen(buff) - 2; i++)
        printf("%c", buff[i]);
    puts("");
    return (SUBSCRIBE);
}