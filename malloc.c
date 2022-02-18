/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-malloc-timothe.coniel
** File description:
** malloc
*/

#include "alloc.h"
#include "tools.h"

void free(void *ptr)
{
    block_t *b;

    if (valid_address(ptr) == 0) {
        b = get_meta(ptr);
        b->free = 1;
    }
}

void *malloc(size_t size)
{
    static block_t *base = NULL;
    block_t *b = base;
    block_t *last;
    size_t data;
    void *test = base;

    data = align4(size);
    if (base) {
        last = base;
        for (; last->next; last = last->next);
        b = find_block(data, base);
        if (b) {
            if ((b->size - data) >= (sizeof(block_t)))
                split_block(b, data);
            b->free = 0;
        } else {
            b = extend_heap(last, data, base);
            if (!b)
                return(NULL);
        }
    } else {
        b = extend_heap(NULL, data, base);
        if (!b)
            return(NULL);
        base = b;
    }
    return((void *)b + sizeof(block_t));
}

void *calloc(size_t nmemb, size_t size)
{
    void *str;
    size_t data = align4(nmemb * size);

    if (nmemb == 0 || size == 0)
        return (NULL);
    str = malloc(nmemb * size);
    if (str != NULL)
        memset(str, 0, nmemb * size);
    else
        return (NULL);
    return (str);
}


void *realloc(void *ptr, size_t size)
{
    block_t *tmp;
    void *new;

    if (!ptr)
        return (malloc(size));
    free(ptr);
    if (!size)
        return (NULL);
    tmp = ptr - sizeof(block_t);
    new = malloc(size);
    if (!new)
        return (NULL);
    memcpy(new, ptr, tmp->size);

    return (new);
}
