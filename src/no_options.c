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
    if ((strace->command = malloc(sizeof(char *) *
        ((ac - i) + 1))) == NULL)
        exit(ERROR);
    for (; i < ac; i++, b++) {
        if ((strace->command[b] = malloc(sizeof(char) *
            (strlen(av[i]) + 1))) == NULL)
            exit(ERROR);
        strcpy(strace->command[b], av[i]);
    }
    strace->command[b] = NULL;
    run_file(strace);
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


int get_env_name_length(char *line)
{
    int len = 0;

    for (int i = 0; line[i] != '\0' && line[i] != '='; len++, i++);
    return (len);
}*/

/*char *search_bin_in_path(char **args, strace_t *strace)
{
    char *bin = NULL;
    char *env_path = get_env_value("PATH", strace->envp);
    char *start = NULL;
    int len = 0;

    if (!env_path)
        return (NULL);
    for (start = env_path; *env_path; env_path += 1) {
        if (*env_path == ':') {
            if ((bin = search_binary_into_dir(args, start, len)))
                return (bin);
            start = env_path + 1;
            len = 0;
        } else
            len++;
    }
    bin = search_binary_into_dir(args, start, len);
    return (bin);
}

char *get_env_value(char *name, char **env)
{
    int name_len = my_strlen(name);
    int env_name_len;

    for (; *env; env++) {
        env_name_len = get_env_name_length(*env);
        if (name_len == env_name_len && !strcmp(*env, name))
            return (*env + env_name_len + 1);
    }
    return (NULL);
}
*/

int run_file(strace_t *strace)
{
    char bin[10];

    if ((strace->prev_pid = fork()) == -1) {
        return (-1);
    } else if (strace->prev_pid == 0) {
        strcpy(bin, "/usr/bin/");
        strcat(bin, strace->command[0]);
        execve(bin, strace->command, strace->envp);
        printf("strace: Can't stat '%s': No such file or directory\n",
            strace->command[0]);
        return (1);
    } else {
        return (0);
    }
    return (1);
}