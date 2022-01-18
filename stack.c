/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD04pm-timothe.coniel
** File description:
** stack
*/

#include "list.h"
#include <stdio.h>
#include "stack.h"


void *stack_top(stack_t stack)
{
    return (list_get_elem_at_back(stack));
}
