/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-malloc-timothe.coniel
** File description:
** malloc
*/

#include "alloc.h"

void split_block(block_t *b, size_t data)
{
    block_t *new = (void *)b + sizeof(block_t) + data;
    new->size = b->size - data - sizeof(block_t);
    new->next = b->next;
    new->free = 1;
    b->size = data;
    b->next = new;
}

block_t *find_block(size_t size)
{
    block_t *optimal = NULL;
    block_t *b = base;

    for (; b; b = b->next)
    {
        if (b->free == 1 && b->size >= size && (optimal == NULL || optimal->size > b->size)) {
            optimal = b;
        }
    }
    return (optimal);
}

block_t *extend_heap(block_t *last, size_t s)
{
    block_t *b = sbrk(0);
    void *full = sbrk(sizeof(block_t) + s);

    if (full < 0)
        return (NULL);
    b->size = s;
    b->next = NULL;
    if (last)
        last->next = b;
    b->free = 0;
    return (b);
}

block_t *get_meta(void *ptr)
{
    return (ptr - sizeof(block_t));
}

int valid_address(void *p)
{
    if (base) {
        if (p > base && p < sbrk(0)) {
            return (p == (get_meta(p))->ptr);
        }
    }
    return (0);
}

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
    block_t *b;
    block_t *last;
    size_t data;

    data = align4(size);
    if (base) {
        last = base;
        for (; last->next; last = last->next);
        b = find_block(data);
        if (b) {
            if ((b->size - data) >= (sizeof(block_t)))
                split_block(b, data);
            b->free = 0;
        } else {
            b = extend_heap(last, data);
            if (!b)
                return(NULL);
        }
    } else {
        b = extend_heap(NULL, data);
        if (!b)
            return(NULL);
        base = b;
    }
    return((void *)b + sizeof(block_t));
}
