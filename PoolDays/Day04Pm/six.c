/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD04pm-timothe.coniel
** File description:
** six
*/

#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void *list_get_elem_at_front(list_t list)
{    
    if (list_is_empty(list) == true)
        return (NULL);
    return (list->value);
}

void *list_get_elem_at_back(list_t list)
{    
    if (list == NULL)
        return (NULL);
    if (list->next == NULL)
        return (list->value);
    while (list->next != NULL)
        list = list->next;
    return (list->value);
}

void *list_get_elem_at_position(list_t list, unsigned int position)
{
    list_t node;

    if (list_get_size(list) < (position + 1)) {
        return (NULL);
    }
    if (position == 0)
        return (list_get_elem_at_front(list));
    node = list;
    while (position != 0) {
        node = node->next;
        position--;
    }
    return (node->value);
}

bool list_del_elem_at_front(list_t *front_ptr)
{
    list_t del_node = (*front_ptr);

    if (list_is_empty(*front_ptr) == true)
        return (false);
    if (del_node->next == NULL) {
        free(*front_ptr);
        *front_ptr = NULL;
        return (true);
    }
    (*front_ptr) = (*front_ptr)->next;
    free(del_node);
    return (true);
}

bool list_del_elem_at_back(list_t *front_ptr)
{
    list_t tmp = *front_ptr;
    list_t last;

    if (front_ptr == NULL || (*front_ptr) == NULL)
        return (false);
    if ((*front_ptr)->next == NULL) {
        free(*front_ptr);
        *front_ptr = NULL;
        return (true);
    }
    while (tmp->next->next != NULL)
        tmp = tmp->next;
    last = tmp->next;
    tmp->next = NULL;
    tmp = last;
    free(last);
    return (true);
}