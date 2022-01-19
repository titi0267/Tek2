/*
** EPITECH PROJECT, 2021
** Paradigms Seminar
** File description:
** Exercice 02
*/

#include <stdio.h>
#include <stdarg.h>
#include "point.h"
#include "raise.h"

typedef struct
{
    Class   base;
    int     x, y;
}   PointClass;

static void Point_set_coords(PointClass *this, int x, int y)
{
    this->x = x;
    this->y = y;
}

static char *Point_to_string(PointClass *this)
{
    char *str = malloc(sizeof(char) * (22 + 13));

    if (str == NULL)
        raise("Out of memory");
    snprintf(str, 35, "<Point (%i, %i)>", this->x, this->y);
    return (str);
}

static void Point_ctor(PointClass *this, va_list *args)
{
    int x = va_arg(*args, int);
    int y = va_arg(*args, int);

    Point_set_coords(this, x, y);
}

static void Point_dtor(PointClass *this)
{
}

// Create additional functions here

static const PointClass _description = {
    {   /* Class struct */
        .__size__ = sizeof(PointClass),
        .__name__ = "Point",
        .__ctor__ = (ctor_t)&Point_ctor,
        .__dtor__ = (dtor_t)&Point_dtor,
        .__str__ = (to_string_t) &Point_to_string,
        .__add__ = NULL,    /* Implement this method for exercice 03 */
        .__sub__ = NULL,    /* Implement this method for exercice 03 */
        .__mul__ = NULL,
        .__div__ = NULL,
        .__eq__ = NULL,
        .__gt__ = NULL,
        .__lt__ = NULL
    },
    .x = 0,
    .y = 0
};

const Class   *Point = (const Class *)&_description;
