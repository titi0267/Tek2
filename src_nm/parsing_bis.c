/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-timothe.coniel
** File description:
** parsing_bis
*/

#include "../include/nm.h"

int file_error(nm_t *nm)
{
    ERROR_FILE(nm->flags[0]);
    nm->error_file += 1;
    return (-1);
}
