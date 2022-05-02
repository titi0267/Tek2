/*
** EPITECH PROJECT, 2022
** ftrace
** File description:
** parse_proc
*/

#include "ftrace.h"

int open_proc(pid_t pid)
{
    char *proc = my_strcat("/proc/", my_getchar((int)pid));
    int fd;
    char *buf = malloc(sizeof(char) * 1000);

    UNUSED(table);
    fd = open(my_strcat(proc, "/maps"), O_RDONLY);
    if (fd == -1)
        return (84);
    read(fd, buf, 1000);
    printf("%s\n", buf);
    return (0);
}