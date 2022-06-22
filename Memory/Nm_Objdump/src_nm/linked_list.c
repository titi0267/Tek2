/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-timothe.coniel
** File description:
** linked_list
*/

#include "../include/nm.h"

int del_elem_at_front(node_t *front_ptr)
{
    node_t del_node = (*front_ptr);

    if (list_is_empty(*front_ptr) == 1)
        return (0);
    if (del_node->next == NULL) {
        free(*front_ptr);
        del_node = NULL;
        return (1);
    }
    (*front_ptr) = (*front_ptr)->next;
    free(del_node);
    reset_positions(front_ptr);
    return (1);
}

int del_elem_at_position(node_t *front_ptr, unsigned int position)
{
    node_t tmp = (*front_ptr);
    node_t node;

    if (front_ptr == NULL)
        return (0);
    for (; tmp->position != position - 1 && tmp != NULL; tmp = tmp->next);
    if (tmp == NULL || tmp->next == NULL)
        return (0);
    node = tmp->next->next;
    free(tmp->next);
    tmp->next = node;
    reset_positions(front_ptr);
    return (1);
}

int node_add_front(node_t *front, node_t node)
{
    node_t new_node;

    if (node->position == 0) {
        node->sorted = -1;
        reset_positions(front);
        return (0);
    }
    new_node = malloc(sizeof(*new_node));
    if (new_node == NULL)
        return (0);
    new_node->sym = node->sym;
    new_node->sorted = -1;
    new_node->position = 0;
    new_node->type = node->type;
    new_node->sym_clear = node->sym_clear;
    new_node->adress = node->adress;
    new_node->next = (*front);
    (*front) = new_node;
    reset_positions(front);
    del_elem_at_position(front, node->position);
    return (1);
}

void list_clear(node_t *front_ptr)
{
    node_t node = *front_ptr;
    node_t next;

    while (node != NULL) {
        next = node->next;
        free(node->sym_clear);
        free(node);
        node = next;
    }
}
