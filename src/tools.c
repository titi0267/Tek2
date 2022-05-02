/*
** EPITECH PROJECT, 2022
** ftrace
** File description:
** tools
*/

#include "ftrace.h"

char *my_strcat(char *begin, char *end)
{
    int begin_lenght = 0;
    int end_lenght = 0;
    int i = 0;
    char *final;

    for (; begin[begin_lenght]; begin_lenght++);
    for (; end[end_lenght]; end_lenght++);
    final = malloc(sizeof(char) * ((end_lenght + begin_lenght) + 2));
    for (int j = 0; begin[j]; j++) {
        final[i] = begin[j];
        i++;
    }
    for (int j = 0; end[j]; j++) {
        final[i] = end[j];
        i++;
    }
    final[i] = '\0';
    return (final);
}

char *my_getchar(int nbr)
{
    int d = 0;
    int tmp;
    char *str;

    for (tmp = nbr; tmp > 0; tmp /= 10, d++);
    str = malloc(sizeof(char) * d + 2);
    for (int x = d - 1; x >= 0; x--) {
        str[x] = (nbr % 10) + 48;
        nbr/=10;
    }
    str[d] = '\0';
    return (str);
}

void useless(void)
{
    UNUSED(table);
}