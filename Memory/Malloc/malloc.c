/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-malloc-timothe.coniel
** File description:
** malloc
*/

#include "alloc.h"
#include "tools.h"

static void *base = NULL;

void free(void *ptr)
{
    block_t *b;

    if (valid_address(ptr, base) == 1) {
        b = get_meta(ptr);
        b->free = 1;
    }
}

void *malloc_sec(block_t *b, size_t data, block_t *last)
{
    if (b) {
        if (b->size >= sizeof(block_t) + data)
            split_block(b, data);
        b->free = 0;
    } else {
        b = extend_heap(last, data);
        if (!b)
            return(NULL);
    }
    return (b);
}

void *malloc(size_t size)
{
    block_t *b = base;
    block_t *last = base;
    size_t data;

    data = align4(size);
    if (base != NULL) {
        for (; last->next; last = last->next);
        b = find_block(data, base);
        b = malloc_sec(b, data, last);
        if (!b)
            return (NULL);
    } else {
        b = extend_heap(NULL, data);
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
    size_t copySize = 0;
    void *new = malloc(size);

    if (!new) {
        free(ptr);
        return (NULL);
    }
    if (!ptr)
        return(new);
    tmp = ptr - sizeof(block_t);
    if (size > tmp->size)
        copySize = tmp->size;
    else
        copySize = size;
    memcpy(new, ptr, copySize);
    free(ptr);
    return (new);
}
