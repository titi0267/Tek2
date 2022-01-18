/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD04pm-timothe.coniel
** File description:
** two
*/

#include "int_list.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


bool int_list_add_elem_at_front(int_list_t *front_ptr, int elem)
{
    int_node_t *new_node = malloc(sizeof(*new_node));

    if (new_node == NULL)
        return (false);
    new_node->value = elem;
    if (int_list_is_empty(*front_ptr) == true) {
        new_node->next = NULL;
        return (true);
    }
    new_node->next = (*front_ptr);
    (*front_ptr) = new_node;
    return (true);
}

bool int_list_add_elem_at_back(int_list_t *front_ptr, int elem)
{
    int_list_t new_node = malloc(sizeof(*new_node));
    int_list_t last_node;
    
    if (new_node == NULL)
        return (false);
    new_node->value = elem;
    new_node->next = NULL;
    if (int_list_is_empty(*front_ptr) == true) {
        (*front_ptr) = new_node;
        return (true);
    }
    last_node = (*front_ptr);
    while (last_node->next != NULL)
        last_node = last_node->next;
    last_node->next = new_node;
    return (true);
}

bool int_list_add_elem_at_position(int_list_t *front_ptr, int elem,
                                    unsigned int position)
{
    int_list_t new_node = malloc(sizeof(*new_node));
    int_list_t next_node = (*front_ptr);
    int_list_t before_node = (*front_ptr);

    if (new_node == NULL)
        return (false);
    new_node->value = elem;
    if (int_list_get_size(*front_ptr) < position || position < 0)
        return (false);
    if (int_list_get_size(*front_ptr) == position)
        return (int_list_add_elem_at_back(front_ptr, elem));
    if (position == 0)
        return (int_list_add_elem_at_front(front_ptr, elem));
    while (position != 0) {
        before_node = next_node;
        next_node = next_node->next;
        position--;
    }
    before_node->next = new_node;
    new_node->next = next_node;
    return (true);
}

bool int_list_is_empty(int_list_t list)
{
    if (list == NULL)
        return (true);
    return (false);
}

unsigned int int_list_get_size (int_list_t list)
{
    unsigned int len = 0;

    if (int_list_is_empty(list) == true)
        return (0);
    for (; list != NULL; list = list->next)
        len++;
    return (len);
}
