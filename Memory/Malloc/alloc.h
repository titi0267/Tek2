/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-malloc-timothe.coniel
** File description:
** alloc
*/

#pragma once

#include <stdio.h>
#include <string.h>
#include <unistd.h>


#define align4(x) (((((x)-1)/4)*4)+4)

#define ERROR 1

typedef struct block_s {
    size_t size;
    struct block_s *next;
    int free;
    void *ptr;
} block_t;

void *malloc(size_t size);
void free(void *ptr) ;
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);
size_t malloc_usable_size(void *ptr);
