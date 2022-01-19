/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGRUSH2-timothe.coniel
** File description:
** new
*/

#include "new.h"
#include "raise.h"
#include <stdlib.h>
#include <stdarg.h>

Object *new(const Class *class, ...)
{
    Object *obj;
    va_list argu_list;

    va_start(argu_list, class);
    obj = va_new(class, &argu_list);
    va_end(argu_list);
    return (obj);
}

Object *va_new(const Class *class, va_list* ap)
{
    Object *obj;

    if (class == NULL)
        raise("Invalid class");
    obj =  malloc(class->__size__);
    if (obj == NULL)
        raise("Out of memory");
    memcpy(obj, class, class->__size__);
    if (class->__ctor__ != NULL)
        class->__ctor__(obj, ap);
    return (obj);
}

void delete(Object *ptr)
{
    Class *class = (Class*) ptr;

    if (ptr == NULL)
        raise("Invalid pointer");
    if (class->__dtor__ != NULL)
        class->__dtor__(ptr);
    free(ptr);
}