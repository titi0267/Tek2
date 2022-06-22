/*
** EPITECH PROJECT, 2022
** B-PSU-402-STG-4-1-strace-timothe.coniel
** File description:
** p_flag
*/

#include "../include/main.h"

int is_num(char c)
{
    if ((c >= 48 && c <= 57))
        return (TRUE);
    return (FALSE);
}

/*
PID doesn't exist :
    printf("strace: attach: ptrace(PTRACE_SEIZE, %i):", strace->pid);
    printf(" No such process\n");
*/
int flag_p(int ac, char **av, int i, strace_t *strace)
{
    if ((i + 1) >= ac) {
        printf("strace: option requires an argument -- 'p'\n");
        printf("Try 'strace -h' for more information.\n");
        return (ERROR);
    }
    for (int c = 0; av[i + 1][c] != '\0'; c++) {
        if (is_num(av[i + 1][c]) == 0) {
            printf("strace: Invalid process id: '%s'\n", av[i + 1]);
            return (ERROR);
        }
    }
    strace->pid = atoi(av[i + 1]);
    printf("pid = %i\n", strace->pid);
    return (0);
}
