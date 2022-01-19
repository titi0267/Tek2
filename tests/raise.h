/*
** EPITECH PROJECT, 2021
** Paradigms Seminar
** File description:
** Exercice 01
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>

#define raise(msg)                                              \
do {                                                            \
    fprintf(stderr, "%s: %u: %s\n", __FILE__, __LINE__, msg);   \
    abort();                                                    \
} while (0)
