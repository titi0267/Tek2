/*
** EPITECH PROJECT, 2022
** teams
** File description:
** save_architecture
*/

#include "../../include/teams.h"

int create_save(void)
{
    if (opendir("./saves") == NULL) {
        if (mkdir("./saves", 0777) == -1 ||
            mkdir("./saves/message", 0777) == -1 ||
            mkdir("./saves/teams", 0777) == -1)
            return (-1);
    }
    return (0);
}