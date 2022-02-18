/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-malloc-timothe.coniel
** File description:
** tools
*/

#pragma once
#include "alloc.h"

block_t *extend_heap(block_t *last, size_t s, void *base);
block_t *get_meta(void *ptr);
int valid_address(void *p);
block_t *find_block(size_t size, void *base);
void split_block(block_t *b, size_t data);
