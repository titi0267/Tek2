/*
** EPITECH PROJECT, 2021
** Paradigms Seminar
** File description:
** Exercice 05
*/

#include <stdio.h>
#include "array.h"
#include "list.h"
#include "int.h"
#include "new.h"

int main(void)
{
    Object *list = new(List, 10, Int, 0);
    Object *it = begin(list);
    Object *it_end;

    push_front(list, -1);
    setitem(list, 5, 12);
    setitem(list, 6, 13);
    pop_back(list);
    pop_back(list);
    pop_back(list);
    push_back(list, 42);
    it_end = end(list);
    printf("array size: %zu\n", len(list));
    while (lt(it, it_end)) {
        printf("%s\n", str(getval(it)));
        incr(it);
    }
    delete(it);
    delete(it_end);
    delete(list);
    return (0);
}

