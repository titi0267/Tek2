/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-malloc-timothe.coniel
** File description:
** alloc
*/

#include <stdio.h>
#include <unistd.h>

#ifndef ALLOC_H_
#define ALLOC_H_

#define align4(x) (((((x)-1)/4)*4)+4)

typedef struct block_s {
    size_t size;
    struct block_s *next;
    int free;
    void *ptr;
} block_t;

static void *base = NULL;

void *malloc(size_t size);
void free(void *ptr) ;
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);

#endif /* !ALLOC_H_ */
