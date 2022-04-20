/*
** EPITECH PROJECT, 2022
** strace
** File description:
** path_command
*/

#include "ftrace.h"

int check_abs(char *command)
{
    UNUSED(table);
    for (int i = 0; command[i]; i++)
        if (command[i] == '/')
            return (1);
    return (0);
}

int check_existence(char *command)
{
    struct stat statbuffer;

    if (stat(command, &statbuffer) == -1)
        return (0);
    return (1);
}

char *stat_binary_path(char **path_command)
{
    for (int i = 0; path_command[i]; i++)
        if (check_existence(path_command[i]))
            return (path_command[i]);
    return (NULL);
}

void free_path_command(char **path_command)
{
    for (int i = 0; path_command[i]; i++)
        free(path_command[i]);
    free(path_command);
}

int path_command(char **command, char **env)
{
    char *path = getenv("PATH");
    char **path_command;
    char *binary;

    if (!path || !strlen(path))
        return (print_error("getenv() error: failed to get PATH\n"));
    path_command = path_to_array(path, command[0]);
    binary = stat_binary_path(path_command);
    if (!binary && !check_existence(command[0])) {
        fprintf(stderr,
        "strace: Can't stat '%s': No such file or directory\n", command[0]);
        free_path_command(path_command);
        return (84);
    }command[0] = (!binary ? command[0] : binary);
    if (fork_and_execve(command, env) == -1) {
        fprintf(stderr, "strace: Can't execve '%s'\n", command[0]);
        free_path_command(path_command);
        return (84);
    }free_path_command(path_command);
    return (0);
}