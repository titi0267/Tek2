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
    if (list_is_empty(list) == true)
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

    if (list_get_size(list) < position) {
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
        del_node = NULL;
        return (true);
    }
    (*front_ptr) = (*front_ptr)->next;
    free(del_node);
    del_node = NULL;
    return (true);
}

bool list_del_elem_at_back(list_t *front_ptr)
{
    list_t del_node = (*front_ptr);
    list_t before = (*front_ptr);

    if (list_is_empty(*front_ptr) == true)
        return (false);
    if (del_node->next == NULL) {
        free(del_node);
        return (true);
    }
    while (del_node->next != NULL) {
        before = del_node;
        del_node = del_node->next;
    }
    before->next  = NULL;
    free(del_node);
}
