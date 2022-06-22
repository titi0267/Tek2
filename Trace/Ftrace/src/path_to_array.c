/*
** EPITECH PROJECT, 2022
** test
** File description:
** path_to_array
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int get_nb_path(char *path)
{
    int ret = 1;

    for (int i = 0; path[i]; i++)
        if (path[i] == ':')
            ret++;
    return (ret);
}

int get_path_length(char *path, int *ii)
{
    int ret = 0;

    for (int i = *ii; path[i] != ':' && path[i]; i++)
        ret++;
    *ii = *ii + ret + 1;
    return (ret);
}

char **path_to_array(char *path, char *command)
{
    int nb_path = get_nb_path(path);
    int ii = 0;
    int iiii = 0;
    int command_len = strlen(command);
    char **path_array = malloc(sizeof(char *) * (nb_path + 1));

    for (int i = 0; i < nb_path; i++) {
        int backup = 0;
        int path_length = get_path_length(path, &ii);
        path_array[i] = malloc(sizeof(char) * (path_length + command_len + 2));
        for ( ; backup < path_length; backup++)
            path_array[i][backup] = path[iiii++];
        path_array[i][backup++] = '/';
        for (int iii = 0; command[iii]; iii++)
            path_array[i][backup++] = command[iii];
        path_array[i][backup] = '\0';
        iiii++;
    }path_array[nb_path] = NULL;
    return (path_array);
}