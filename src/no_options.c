/*
** EPITECH PROJECT, 2022
** B-PSU-402-STG-4-1-strace-timothe.coniel
** File description:
** no_options
*/

#include "../include/main.h"

int no_options(int ac, char **av, int i, strace_t *strace)
{
    int b = 0;

    strace->is_command = TRUE;
    if ((strace->command = malloc(sizeof(char *) * ((ac - i) + 1))) == NULL)
        exit(ERROR);
    for (; i < ac; i++, b++) {
        if ((strace->command[b] = malloc(sizeof(char) * (strlen(av[i]) + 1))) == NULL)
            exit(ERROR);
        strcpy(strace->command[b], av[i]);
    }
    strace->command[b] = NULL;
    return (0);
}

/*
int execute_command(char **args, char next, shell_t *shell)
{
    char *bin = NULL;
    int status = 0;

    if ((bin = search_binary(args, shell)) != NULL) {
        status = run_file(bin, args, next, shell);
        free(bin);
        return (0);
    } else {
        if (errno && errno != 2)
            print_err(args[0]);
        else {
            write(2, args[0], my_strlen(args[0]));
            write(2, ": Command not found.\n", 21);
        }
        return (1);
    }
}
*/

int run_file(char *bin, char **args, char next, strace_t *strace)
{
    if ((strace->prev_pid = fork()) == -1) {
        return (-1);
    } else if (strace->prev_pid == 0) {
        for (int i = 3; i < 16; i++)
            close(i);
        execve(bin, args, strace->env);
        printf("strace: Can't stat '%s': No such file or directory\n",
            strace->command[0]);
        return (1);
    } else {
        return (0);
    }
    return (1);
}