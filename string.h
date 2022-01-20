/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD05-timothe.coniel
** File description:
** string
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef STRING_H_
#define STRING_H_

typedef struct string_s string_t;

struct string_s {
    char *str;
    void (*assign_c)(string_t *this, const char *s);
    void (*append_c)(string_t *this, const char *ap);
    void (*assign_s)(string_t *this, const string_t *str);
    void (*append_s)(string_t *this, const string_t *ap);
};

void append_s(string_t *this, const string_t *ap);
void append_c(string_t *this, const char *ap);
void assign_c(string_t *this, const char *s);
void assign_s(string_t *this, const string_t *str);
void string_destroy(string_t *this);
void string_init(string_t *this, const char *s);

#endif /* !STRING_H_ */
