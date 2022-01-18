/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD04pm-timothe.coniel
** File description:
** four
*/

#include "list.h"
#include <stdio.h>
#include <stdlib.h>

bool list_del_elem_at_position(list_t * front_ptr, unsigned int position)
{
    list_t tmp = *front_ptr;
    list_t node;

    if (front_ptr == NULL)
        return (false);
    if (position == 0)
        return (list_del_elem_at_front(front_ptr));
    for (unsigned int i = 0; i != (position - 1) && tmp != NULL; i++)
        tmp = tmp->next;
    if (tmp == NULL || tmp->next == NULL)
        return (false);
    node = tmp->next->next;
    free(tmp->next);
    tmp->next = node;
    return (true);
}

void list_clear(list_t *front_ptr)
{
    list_t tmp;

    while (*front_ptr != NULL)
    {
       tmp = *front_ptr;
       *front_ptr = (*front_ptr)->next;
       free(tmp);
    }
}

void list_dump(list_t list, value_displayer_t val_disp)
{
    for (; list != NULL; list = list->next) {
        val_disp(list->value);
    }
}