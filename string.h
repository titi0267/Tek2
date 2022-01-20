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
    char (*at)(const string_t * this, size_t pos);
    void (*clear)(string_t *this);
    int (*length)(const string_t *this);
    int (*compare_s)(const string_t *this, const string_t *str);
    int (*compare_c)(const string_t *this, const char *str);
    size_t (*copy)(const string_t * this, char *s, size_t n, size_t pos);
    const char * (*c_str)(const string_t *this);
    int (*empty)(const string_t *this);
};

void append_s(string_t *this, const string_t *ap);
void append_c(string_t *this, const char *ap);
void assign_c(string_t *this, const char *s);
void assign_s(string_t *this, const string_t *str);
void string_destroy(string_t *this);
void string_init(string_t *this, const char *s);
char at(const string_t * this, size_t pos);
void clear(string_t *this);
int length(const string_t *this);
int compare_s(const string_t *this, const string_t *str);
int compare_c(const string_t *this, const char *str);
size_t copy(const string_t * this, char *s, size_t n, size_t pos);
const char *c_str(const string_t *this);
int empty(const string_t * this);

#endif /* !STRING_H_ */
