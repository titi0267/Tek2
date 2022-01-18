/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD04pm-timothe.coniel
** File description:
** five
*/

#include "list.h"
#include <stdio.h>
#include <stdlib.h>

unsigned int list_get_size (list_t list)
{
    unsigned int len = 0;

    if (list_is_empty(list) == true)
        return (0);
    for (; list != NULL; list = list->next)
        len++;
    return (len);
}

bool list_is_empty(list_t list)
{
    if (list == NULL)
        return (true);
    return (false);
}

bool list_add_elem_at_front(list_t *front_ptr, void *elem)
{
    list_t new_node = malloc(sizeof(*new_node));

    if (new_node == NULL)
        return (false);
    new_node->value = elem;
    new_node->next = (*front_ptr);
    (*front_ptr) = new_node;
    return (true);
}

bool list_add_elem_at_back(list_t *front_ptr, void *elem)
{
    list_t new_node = malloc(sizeof(*new_node));
    list_t last_node;
    
    if (new_node == NULL)
        return (false);
    new_node->value = elem;
    new_node->next = NULL;
    if (list_is_empty(*front_ptr) == true) {
        (*front_ptr) = new_node;
        return (true);
    }
    last_node = (*front_ptr);
    while (last_node->next != NULL)
        last_node = last_node->next;
    last_node->next = new_node;
    return (true);
}

bool list_add_elem_at_position(list_t *front_ptr, void *elem,
                                    unsigned int position)
{
    list_t new_node = malloc(sizeof(*new_node));
    list_t next_node = (*front_ptr);
    list_t before_node = (*front_ptr);

    if (new_node == NULL || list_get_size(*front_ptr) < (position + 1))
        return (false);
    new_node->value = elem;
    if (position == 0) {
        free(new_node);
        return (list_add_elem_at_front(front_ptr, elem));
    }
    while (position != 0) {
        before_node = next_node;
        next_node = next_node->next;
        position--;
    }
    before_node->next = new_node;
    new_node->next = next_node;
    return (true);
}
