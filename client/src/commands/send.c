/*
** EPITECH PROJECT, 2022
** teams
** File description:
** send
*/

#include "../../include/command.h"

int c_send(char *buff)
{
    if (check_is_arg(buff) == CMD_ERROR)
        return (CMD_ERROR);
    for (int i = 0; buff[2] != '"'; i++, buff++) {
        if (buff[2] < 48 || buff[2] > 57 || i > MAX_NAME_LENGTH) {
            return (CMD_ERROR);
        }
    }
    if (check_is_arg(buff + 3) == CMD_ERROR)
        return (CMD_ERROR);
    for (int i = 5; buff[i] != '"'; i++) {
        if (i > MAX_BODY_LENGTH)
            return (CMD_ERROR);
    }
    printf("Send: ");
    for (int i = 5; buff[i] != '\n'; i++)
        (buff[i] == '"') ? puts("") : printf("%c", buff[i]);
    return (SEND);
}