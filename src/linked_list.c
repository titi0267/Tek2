/*
** EPITECH PROJECT, 2022
** ftrace
** File description:
** linked_list
*/

#include "ftrace.h"

int list_is_empty(node_t list)
{
    if (list == NULL)
        return (1);
    return (0);
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
    UNUSED(table);
    return (1);
}

int print_list(node_t list)
{
    int len = 0;

    if (list_is_empty(list) == 1)
        return (0);
    //i++;
    //printf("i = %i\n", i);
    for (; list != NULL; list = list->next) {
        /*if (strcmp(list->sym, "main") == 0)
            printf("%llx\n", list->adress);*/
        //if (list->type == 'T')
            //printf("%s\n", list->sym);
        len++;
    }
        /*if (list->type == 'T')
            printf("%s\n", list->sym);
    }*/

    return (len);
}