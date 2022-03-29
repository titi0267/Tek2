/*
** EPITECH PROJECT, 2022
** B-PSU-402-STG-4-1-strace-timothe.coniel
** File description:
** main
*/

#include "../include/main.h"

int usage(void)
{
    printf("USAGE: ./strace [-s] [-p <pid>|<command>]\n");

    return (ERROR);
}

int flags(int ac, char **av, strace_t *strace)
{
    int error = 1;
    int i = 1;

    for (; i < ac; i++) {
        if (strcmp("-p", av[i]) != 0 && strcmp("-s", av[i]) != 0)
            break;
        if (strcmp("-p", av[i]) == 0 &&
            (error = (flag_p(ac, av, i, strace) != ERROR)))
            i++;
        else if (strcmp("-s", av[i]) == 0)
            error = flag_s();
        if (error == FALSE)
            return (ERROR);
    }
    if (i < ac) {
        no_options(ac, av, i, strace);
    }
    return (0);
}

void free_func(strace_t *strace)
{
    if (strace->is_command == TRUE) {
        for (int i = 0; strace->command[i] != NULL; i++)
            free(strace->command[i]);
        free(strace->command);
    }
    for (int i = 0; strace->envp[i] != NULL; i++)
        free(strace->envp[i]);
    free(strace->envp);
    free(strace);
}

char **copy_env(char **env, strace_t *strace)
{
    int i = 0;

    for (; env[i] != NULL; i++);
    if ((strace->envp = malloc(sizeof(char *) * (i + 1))) == NULL)
        exit(ERROR);
    for (i = 0; env[i] != NULL; i++) {
        if ((strace->envp[i] = malloc(sizeof(char) *
            (strlen(env[i]) + 1))) == NULL)
            exit(ERROR);
        strcpy(strace->envp[i], env[i]);
    }
    strace->envp[i] = NULL;
}

int main(int ac, char **av, char **env)
{
    strace_t *strace;
    int error = 0;

    if (ac == 1)
        return (ERROR);
    if (strcmp("--help", av[1]) == 0)
        return (usage());
    if ((strace = malloc(sizeof(strace_t))) == NULL)
        return (ERROR);
    strace->is_command = FALSE;
    copy_env(env, strace);
    error = flags(ac, av, strace);
    free_func(strace);
    return (error);
}