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

int flags(int ac, char **av, char **env)
{
    int error = 0;

    if (strcmp("--help", av[1]) == 0)
        return (usage());
    for (int i = 1; i < ac; i++) {
        if (strcmp("-p", av[i]) == 0)
            error = flag_p(ac, av, i);
        else if (strcmp("-s", av[i]) == 0)
            error = flag_s();
        else {
            no_options(ac, av, i);
            //printf("Unknown flag: %s\n", av[i]);
        }
        if (error == ERROR)
            return (ERROR);
        if (strcmp("-p", av[i]) == 0)
            i++;
    }
    return (error);
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
    strace = malloc(sizeof(strace_t));
    copy_env(env, strace);
    //error = flags(ac, av, env);
    free_func(strace);
    return (error);
}