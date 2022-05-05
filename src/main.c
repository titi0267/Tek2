/*
** EPITECH PROJECT, 2022
** STRACE
** File description:
** main
*/

#include "ftrace.h"

int print_error(char *what)
{
    write(2, what, strlen(what));
    return (ERROR);
}

static int usage(void)
{
    write(1, "USAGE: ./ftrace <command>\n", 26);
    return (0);
}

int main(int ac, char **av, char **env)
{
    ftrace_t *ftrace;
    UNUSED(table);
    if (ac < 2)
        return (print_error("Not enough argument\n"));
    if (ac == 2 && strcmp("--help", av[1]) == 0)
        return (usage());
    ftrace = malloc(sizeof(ftrace_t));
    ftrace->maps = malloc(sizeof(maps_file_t) * 20);
    if (ftrace->maps == NULL)
        printf("It is NULL omg\n");
    ftrace->maps_init = 0;
    for (int i = 0; i < 20; i++) {
        ftrace->maps[i].last_array = -1;
    }
    if (elf_version(EV_CURRENT) == EV_NONE)
        printf("failed\n");
    return (ftrace_command(++av, env, ftrace));
}