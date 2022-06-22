/*
** EPITECH PROJECT, 2022
** teams
** File description:
** convertion
*/

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/communication.h"

char *increment_str(int id)
{
    char *buff = malloc(MAX_NAME_LENGTH);

    sprintf(buff, "%d", id + 1);
    return (buff);
}