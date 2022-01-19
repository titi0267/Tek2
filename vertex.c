/*
** EPITECH PROJECT, 2021
** Paradigms Seminar
** File description:
** Exercice 02
*/

#include <stdio.h>
#include <stdarg.h>
#include "vertex.h"
#include "raise.h"
#include "new.h"

typedef struct
{
    Class   base;
    int     x, y, z;
}   VertexClass;

static void Vertex_set_coords(VertexClass *this, int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

static char *Vertex_to_string(VertexClass *this)
{
    char *str = malloc(sizeof(char) * (33 + 16));

    if (str == NULL)
        raise("Out of memory");
    snprintf(str, 48, "<Vertex (%i, %i, %i)>", this->x, this->y, this->z);
    return (str);
}

static Object *Vertex_add(VertexClass *this, VertexClass *other)
{
    int x = this->x + other->x;
    int y = this->y + other->y;
    int z = this->z + other->z;

    return (new(Vertex, x, y, z));
}

static Object *Vertex_sub(VertexClass *this, VertexClass *other)
{
    int x = this->x - other->x;
    int y = this->y - other->y;
    int z = this->z - other->z;

    return (new(Vertex, x, y, z));
}
static void Vertex_ctor(VertexClass *this, va_list *args)
{
    int x = va_arg(*args, int);
    int y = va_arg(*args, int);
    int z = va_arg(*args, int);

    Vertex_set_coords(this, x, y, z);
}

static void Vertex_dtor(VertexClass *this)
{
    (void) this;
}

// Create additional functions here

static const VertexClass _description = {
    {   /* Class struct */
        .__size__ = sizeof(VertexClass),
        .__name__ = "Vertex",
        .__ctor__ = (ctor_t)&Vertex_ctor,
        .__dtor__ = (dtor_t)&Vertex_dtor,
        .__str__ = (to_string_t) &Vertex_to_string,
        .__add__ = (binary_operator_t) &Vertex_add,
        .__sub__ = (binary_operator_t) &Vertex_sub,
        .__mul__ = NULL,
        .__div__ = NULL,
        .__eq__ = NULL,
        .__gt__ = NULL,
        .__lt__ = NULL
    },
    .x = 0,
    .y = 0,
    .z = 0,
};

const Class   *Vertex = (const Class *)&_description;

