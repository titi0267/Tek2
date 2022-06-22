/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-malloc-timothe.coniel
** File description:
** sec_tools
*/

#include "alloc.h"
#include "tools.h"

size_t malloc_usable_size(void *ptr)
{
    if (!ptr)
        return (0);
    return (get_meta(ptr)->size);
}

void *reallocarray(void *ptr, size_t nmemb ,size_t size)
{
    return (realloc(ptr, nmemb * size));
}
