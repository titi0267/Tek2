/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGRUSH2-timothe.coniel
** File description:
** int
*/

#include "int.h"
#include <stdarg.h>
#include "raise.h"
#include "new.h"

typedef struct
{
    Class base;
    int x;
} IntClass;

static char *Int_to_string(IntClass *this)
{
    char *str = malloc(sizeof(char) * (20));

    if (str == NULL)
        raise("Out of memory");
    snprintf(str, 19, "<Int (%i)>", this->x);
    return (str);
}

static Object *Int_add(IntClass *this, IntClass *other)
{
    int x = this->x + other->x;

    return (new(Int, x));
}

static Object *Int_sub(IntClass *this, IntClass *other)
{
    int x = this->x - other->x;

    return (new(Int, x));
}

static Object *Int_mul(IntClass *this, IntClass *other)
{
    int x = this->x * other->x;

    return (new(Int, x));
}

static Object *Int_div(IntClass *this, IntClass *other)
{
    int x;

    if (other->x == 0)
        raise("Div by 0");
    x = this->x / other->x;
    return (new(Int, x));
}

static bool Int_eq(IntClass *this, IntClass *other)
{
    return (this->x == other->x);
}

static bool Int_gt(IntClass *this, IntClass *other)
{
    return (this->x > other->x);
}

static bool Int_lt(IntClass *this, IntClass *other)
{
    return (this->x < other->x);
}

static void Int_ctor(IntClass *this, va_list *args)
{
    int x = va_arg(*args, int);

    this->x = x;
}

static void Int_dtor(IntClass *this)
{
    (void) this;
}

static const IntClass _description = {
    {/* Class struct */
     .__size__ = sizeof(IntClass),
     .__name__ = "Int",
     .__ctor__ = (ctor_t)&Int_ctor,
     .__dtor__ = (dtor_t)&Int_dtor,
     .__str__ = (to_string_t)&Int_to_string,
     .__add__ = (binary_operator_t)&Int_add,
     .__sub__ = (binary_operator_t)&Int_sub,
     .__mul__ = (binary_operator_t)&Int_mul,
     .__div__ = (binary_operator_t)&Int_div,
     .__eq__ = (binary_comparator_t)&Int_eq,
     .__gt__ = (binary_comparator_t)&Int_gt,
     .__lt__ = (binary_comparator_t)&Int_lt},
    .x = 0,
    };

const Class *Int = (const Class *)&_description;
