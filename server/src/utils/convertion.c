/*
** EPITECH PROJECT, 2022
** teams
** File description:
** convertion
*/

#include <stdio.h>
#include <stdlib.h>

char *increment_str(char *str)
{
    int id = atoi(str);
    char *buff;

    sprintf(buff, "%d", id + 1);
    return (buff);
}