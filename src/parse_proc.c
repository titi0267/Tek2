/*
** EPITECH PROJECT, 2022
** ftrace
** File description:
** parse_proc
*/

#include <stdio.h>
#include "ftrace.h"

int nm_bin(char *buf, ftrace_t *ftrace)
{
    char *address = malloc(sizeof(char) * 13);
    Elf64_Ehdr *elf;
    void *ptr;

    strncpy(address, buf, 12);
    address[13] = '\0';
    puts(address);
    sscanf(address, "%lx", (unsigned long*) &ptr);
    printf("--> %lx\n", (unsigned long) address);
    elf = (Elf64_Ehdr *)ptr;
    if (elf->e_ident[EI_CLASS] == ELFCLASS64)
        printf("It is a 64bit elf\n");
    return (0);
}

int find_binary(char *buf, ftrace_t *ftrace)
{
    int i = 0;
    int cmd_len = strlen(ftrace->bin_name) - 1;

    if (buf == NULL)
        return (84);
    for (; buf[i] != '\n'; i++);
    i--;
    for (; buf[i] != '/'; i--, cmd_len--) {
        if (buf[i] != ftrace->bin_name[cmd_len])
            break;
    }
    if (cmd_len == 0 || ftrace->bin_name[cmd_len] == '/')
        nm_bin(buf, ftrace);
    return (0);
}

int open_proc(pid_t pid, ftrace_t *ftrace)
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
    find_binary(buf, ftrace);
    free(buf);
    return (0);
}
