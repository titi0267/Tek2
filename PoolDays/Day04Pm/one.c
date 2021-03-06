/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD04pm-timothe.coniel
** File description:
** test
*/

#include "int_list.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


bool int_list_del_elem_at_front(int_list_t *front_ptr)
{
    int_list_t del_node = (*front_ptr);

    if (int_list_is_empty(*front_ptr) == true)
        return (false);
    if (del_node->next == NULL) {
        free(*front_ptr);
        del_node = NULL;
        return (true);
    }
    (*front_ptr) = (*front_ptr)->next;
    free(del_node);
    return (true);
}

bool int_list_del_elem_at_back(int_list_t *front_ptr)
{
    int_list_t del_node = (*front_ptr);
    int_list_t before = (*front_ptr);

    if (int_list_is_empty(*front_ptr) == true) {
        return (false);
    }
    if (del_node->next == NULL) {
        free(*front_ptr);
        *front_ptr = NULL;
        return (true);
    }
    while (del_node->next != NULL) {
        before = del_node;
        del_node = del_node->next;
    }
    before->next  = NULL;
    free(del_node);
    return (true);
}

bool int_list_del_elem_at_position(int_list_t * front_ptr, unsigned int position)
{
    int_list_t tmp = *front_ptr;
    int_list_t node;

    if (front_ptr == NULL)
        return (false);
    if (position == 0)
        return (int_list_del_elem_at_front(front_ptr));
    for (unsigned int i = 0; i != (position - 1) && tmp != NULL; i++)
        tmp = tmp->next;
    if (tmp == NULL || tmp->next == NULL)
        return (false);
    node = tmp->next->next;
    free(tmp->next);
    tmp->next = node;
    return (true);
}

void int_list_clear(int_list_t *front_ptr)
{
    int_list_t node = *front_ptr;
    int_list_t next;

    while (node != NULL) {
        next = node->next;
        free(node);
        node = next;
    }
}
