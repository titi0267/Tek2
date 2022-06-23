/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD04pm-timothe.coniel
** File description:
** queue_one
*/

#include "list.h"
#include "queue.h"
#include <stdio.h>

void *queue_front(queue_t queue)
{
    return (list_get_elem_at_back(queue));
}
