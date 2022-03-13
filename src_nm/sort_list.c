/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-timothe.coniel
** File description:
** sort_list
*/

#include "../include/nm.h"

int my_strcmp_ssec(const char *s2, int i)
{
    if (s2[i] == '@')
        return (-1);
    return (1);
}

int my_strcmp_at(const char *s1, const char *s2, int i)
{
    if (s1[i] == '@' || s2[i] == '@')
        return (1);
    return (-1);
}

int my_strcmp(const char *s1, const char *s2)
{
    int a = strlen(s1);
    int b = strlen(s2);
    int c;

    c = (strlen(s1) < strlen(s2)) ? b : a;
    for (int i = 0; i != c; i++) {
        if (s1[i] > s2[i])
            return (my_strcmp_ssec(s2, i));
        else if (s1[i] < s2[i])
            return (my_strcmp_at(s1, s2, i));
    }
    return (0);
}

node_t new_highest(int b, node_t node, node_t find_node)
{
    if (b < 0 && node->sorted != -1) {
        find_node = node;
    } else if (b == 0 && node->sorted != -1) {
        if (my_strcmp(find_node->sym, node->sym) < 0)
            find_node = node;
    }
    return (find_node);
}

node_t find_highest(node_t *front)
{
    node_t find_node = (*front);
    node_t node = (*front);
    int b = 0;

    for (; node->sorted == -1 && node != NULL; node = node->next);
    find_node = node;
    for (; node != NULL; node = node->next)
        find_node = new_highest(
            my_strcmp(find_node->sym_clear, node->sym_clear), node, find_node);
    return (find_node);
}
