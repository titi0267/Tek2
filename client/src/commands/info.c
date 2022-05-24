/*
** EPITECH PROJECT, 2022
** teams
** File description:
** info
*/

#include "../../include/command.h"

int c_info(char *buff)
{
    if (buff[0] != '\n')
        return (CMD_ERROR);
    printf("info\n");
    return (INFO);
}