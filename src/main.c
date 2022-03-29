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
        if (strcmp("-p", av[i]) != 0 && strcmp("-s", av[i]) != 0) {
            printf("av = %s\n", av[i]);
            break;
        }
        if (strcmp("-p", av[i]) == 0 &&
            (error = (flag_p(ac, av, i, strace) != ERROR)))
            i++;
        else if (strcmp("-s", av[i]) == 0)
            error = flag_s();
        if (error == FALSE)
            return (ERROR);
    }
    if (i < ac)
        no_options(ac, av, i, strace);
    return (0);
}

void free_func(strace_t *strace)
{
    for (int i = 0; strace->envp[i] != NULL; i++) {
        free(strace->envp[i]);
    }
    free(strace->envp);
    free(strace);
}

char **copy_env(char **env, strace_t *strace)
{
    int i = 0;

    for (; env[i] != NULL; i++);
    strace->envp = malloc(sizeof(char *) * (i + 1));
    for (i = 0; env[i] != NULL; i++) {
        strace->envp[i] = malloc(sizeof(char) * (strlen(env[i]) + 1));
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
    strace = malloc(sizeof(strace_t));
    copy_env(env, strace);
    error = flags(ac, av, strace);
    free_func(strace);
    return (error);
}