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
    UNUSED(table);
    if (ac < 2)
        return (print_error("Not enough argument\n"));
    if (ac == 2 && strcmp("--help", av[1]) == 0)
        return (usage());
    return (ftrace_command(++av, env));
}