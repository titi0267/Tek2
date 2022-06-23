/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGRUSH2-timothe.coniel
** File description:
** list_methods
*/

#ifndef LIST_METHODS_H_
#define LIST_METHODS_H_

#include "container.h"

typedef struct ListMethods_s ListMethods;

typedef void (*push_front_t)(ListMethods *this, ...);
typedef void (*push_back_t)(ListMethods *this, ...);
typedef void (*pop_front_t)(ListMethods *this);
typedef void (*pop_back_t)(ListMethods *this);

typedef Object *(*get_front_t)(ListMethods *this);
typedef Object *(*get_back_t)(ListMethods *this);

struct ListMethods_s
{
    Container base;
    push_front_t __push_front__;
    push_back_t __push_back__;
    pop_front_t __pop_front__;
    pop_back_t __pop_back__;
    get_front_t __front__;
    get_back_t __back__;
};

#define push_front(lm, ...) ((ListMethods *)lm)->__push_front__(lm, __VA_ARGS__)
#define push_back(lm, ...)  ((ListMethods *)lm)->__push_back__(lm, __VA_ARGS__)
#define pop_front(lm)       ((ListMethods *)lm)->__pop_front__(lm)
#define pop_back(lm)        ((ListMethods *)lm)->__pop_back__(lm)
#define front(lm)           ((ListMethods *)lm)->__front__(lm)
#define back(lm)            ((ListMethods *)lm)->__back__(lm)

#endif /* !LIST_METHODS_H_ */
