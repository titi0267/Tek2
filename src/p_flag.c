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

int flag_p(int ac, char **av, int i)
{
    if ((i + 1) >= ac) {
        printf("Missing PID with -p\n");
        return (ERROR);
    }
    for (int c = 0; av[i + 1][c] != '\0'; c++) {
        if (is_num(av[i + 1][c]) == 0) {
            printf("Invalid or missing PID\n");
            return (ERROR);
        }
    }
    printf("P is flags\n");
    return (0);
}
