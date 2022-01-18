/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD04pm-timothe.coniel
** File description:
** three
*/

#include "int_list.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void int_list_dump(int_list_t list)
{
    for (; list != NULL; list = list->next)
        printf("%d\n", list->value);
}

int int_list_get_elem_at_front(int_list_t list)
{    
    if (int_list_is_empty(list) == true)
        return (0);
    return (list->value);
}

int int_list_get_elem_at_back(int_list_t list)
{    
    if (int_list_is_empty(list) == true)
        return (0);
    if (list->next == NULL)
        return (list->value);
    while (list->next != NULL)
        list = list->next;
    return (list->value);
}

int int_list_get_elem_at_position(int_list_t list, unsigned int position)
{
    int_list_t node;

    if (int_list_get_size(list) < position || position < 0) {
        return (false);
    }
    if (int_list_get_size(list) == position)
        return (int_list_get_elem_at_back(list));
    if (position == 0)
        return (int_list_get_elem_at_front(list));
    node = list;
    while (position != 0) {
        node = node->next;
        position--;
    }
    return (node->value);
}
