/*
** EPITECH PROJECT, 2021
** Paradigms Seminar
** File description:
** Exercice 02
*/

#include <stdio.h>
#include <stdarg.h>
#include "raise.h"
#include "new.h"
#include "char.h"

typedef struct
{
    Class   base;
    char     c;
}   CharClass;

static char *Char_to_string(CharClass *this)
{
    char *str = malloc(sizeof(char) * (15));

    if (str == NULL)
        raise("Out of memory");
    snprintf(str, 14, "<Char (%hhi)>", this->c);
    return (str);
}

static Object *Char_add(CharClass *this, CharClass *other)
{
    char added = this->c + other->c;

    return (new(Char, added));
}

static Object *Char_sub(CharClass *this, CharClass *other)
{
    char subbed = this->c - other->c;

    return (new(Char, subbed));
}

static Object *Char_mul(CharClass *this, const CharClass *other)
{
    char res = this->c * other->c;

    return (new(Char, res));
}

static Object *Char_div(CharClass *this, const CharClass *other)
{
    char res;

    if (other->c == 0)
        raise("Invalid division");
    res = this->c / other->c;
    return (new(Char, res));
}

static bool Char_is_eq(CharClass *this, const CharClass *other)
{
    return (this->c == other->c);
}

static bool Char_is_lt(CharClass *this, const CharClass *other)
{
    return (this->c < other->c);
}

static bool Char_is_gt(CharClass *this, const CharClass *other)
{
    return (this->c > other->c);
}

static void Char_ctor(CharClass *this, va_list *args)
{
    this->c = va_arg(*args, char);
}

static void Char_dtor(CharClass *this)
{
}

// Create additional functions here

static const CharClass _description = {
    {   /* Class struct */
        .__size__ = sizeof(CharClass),
        .__name__ = "Char",
        .__ctor__ = (ctor_t)&Char_ctor,
        .__dtor__ = (dtor_t)&Char_dtor,
        .__str__ = (to_string_t) &Char_to_string,
        .__add__ = (binary_operator_t) &Char_add,
        .__sub__ = (binary_operator_t) &Char_sub,
        .__mul__ = (binary_operator_t) &Char_mul,
        .__div__ = (binary_operator_t) &Char_div,
        .__eq__ = (binary_operator_t) &Char_is_eq,
        .__gt__ = (binary_operator_t) &Char_is_gt,
        .__lt__ = (binary_operator_t) &Char_is_lt
    },
    .c = 0,
};

const Class   *Char = (const Class *)&_description;

