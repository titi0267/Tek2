/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-timothe.coniel
** File description:
** linked_list_bis
*/

#include "../include/nm.h"

int list_is_empty(node_t list)
{
    if (list == NULL)
        return (1);
    return (0);
}

void reset_positions(node_t *front)
{
    node_t list = (*front);

    for (int i = 0; list != NULL; list = list->next, i++)
        list->position = i;
}

int get_list_size(node_t list)
{
    int len = 0;

    if (list_is_empty(list) == 1)
        return (0);
    for (; list != NULL; list = list->next)
        len++;
    return (len);
}

int create_list(node_t *front, char *name, int i, Elf64_Addr addr)
{
    node_t new_node = malloc(sizeof(*new_node));

    if (new_node == NULL)
        return (0);
    new_node->sym = name;
    new_node->sorted = 1;
    new_node->position = i;
    new_node->adress = addr;
    new_node->next = (*front);
    (*front) = new_node;
    return (1);
}

void nm_output(node_t list, nm_t *nm)
{
    if (list_is_empty(list) == 1)
        return;
    for (; list != NULL; list = list->next) {
        if (nm->file_type == OBJ && list->position == 0)
            printf("%016x %c %s\n", list->adress, list->type, list->sym);
        else if (list->adress == NULL)
            printf("                 %c %s\n", list->type, list->sym);
        else
            printf("%016x %c %s\n", list->adress, list->type, list->sym);
    }
}
