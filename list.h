/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGRUSH2-timothe.coniel
** File description:
** list
*/

#ifndef LIST_H_
#define LIST_H_

#include "container.h"

typedef void (*push_front_t)(Object *this, Object *obj);
typedef void (*push_back_t)(Object *this, Object *obj);
typedef void (*pop_front_t)(Object *this);
typedef void (*pop_back_t)(Object *this);

typedef Object *(*get_front_t)(Object *this);
typedef Object *(*get_back_t)(Object *this);

extern const Class *List;

#endif /* !LIST_H_ */
