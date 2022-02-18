/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-malloc-timothe.coniel
** File description:
** tools
*/

#include "alloc.h"

void split_block(block_t *b, size_t data)
{
    block_t *new = (void *)b + sizeof(block_t) + data;
    new->size = b->size - data - sizeof(block_t);
    new->next = b->next;
    new->free = 1;
    new->ptr = new;
    b->size = data;
    b->next = new;
}

block_t *find_block(size_t size, void *base)
{
    block_t *optimal = NULL;
    block_t *b = base;

    for (; b; b = b->next)
    {
        if (b->free == 1 && b->size >= size && (optimal == NULL
            || optimal->size > b->size)) {
            optimal = b;
        }
    }
    return (optimal);
}

/*static int page = 0;
    int total_size = 0;
    int page_to_malloc = 0;
    block_t *tmp = base;
    for (; tmp; total_size += tmp->size, tmp = tmp->next);
    if ((total_size + sizeof(block_t) + s) > (page * getpagesize())) {
        for (; page_to_malloc < (sizeof(block_t) + s); page_to_malloc += 2);
        page += page_to_malloc;
    }
    block_t *b = sbrk(0);
    void *full = sbrk(sizeof(block_t) + s);// + (page_to_malloc * getpagesize()));

    if (full < 0)
        return (NULL);
    b->size = s;
    b->next = NULL;
    if (last)
        last->next = b;
    b->free = 0;
    return (b);*/

block_t *extend_heap(block_t *last, size_t s, void *base)
{
    block_t *b = sbrk(0);
    block_t *empty;
    size_t pageSize = 0;
    void* sb;

    for (; pageSize < (sizeof(block_t) + s); pageSize += getpagesize() * 2);
    sb = sbrk(pageSize);
    if (sb < 0)
        return (NULL);
    b->size = s;
    empty = (void *)b + sizeof(block_t) + s;
    empty->size = pageSize - s - sizeof(block_t);
    empty->next = NULL;
    b->next = empty;
    if (last)
        last->next = b;
    b->free = 0;
    empty->free = 1;
    return (b);
}

block_t *get_meta(void *ptr)
{
    return (ptr - sizeof(block_t));
}

int valid_address(void *p)
{
    if (p) {
        if (p < sbrk(0)) {
            return (p == (get_meta(p))->ptr);
        }
    }
    return (1);
}
