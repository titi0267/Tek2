/*
** EPITECH PROJECT, 2022
** float.c
** File description:
** float
*/
#include "float.h"
#include "new.h"
#include "string.h"

typedef struct
{
    Class   base;
    float     x;
}   FloatClass;

static Object *Float_add_float(FloatClass *this, FloatClass *other);
static Object *Float_add_int(FloatClass *this, Object *other);

static char *Float_to_string(FloatClass *this)
{
    char *str = malloc(sizeof(char) * (32 + 10));

    if (str == NULL)
        raise("Out of memory");
    snprintf(str, 42, "<Float (%f)>", this->x);
    return (str);
}



static void Float_ctor(FloatClass *this, va_list *args)
{
    float x = va_arg(*args, double);

    this->x = x;
}

static void Float_dtor(FloatClass *this)
{
    (void) this;
}

static Object *Float_add_type(FloatClass *this, Object *obj)
{
    if (strcmp("Float", ((Class*)obj)->__name__) == 0)
        return Float_add_float(this, obj);
    if (strcmp("Int", ((Class*)obj)->__name__) == 0)
        return Float_add_int(this, obj);
}

static Object *Float_add_int(FloatClass *this, Object *other)
{
    float y = this->x + (float)Int_get_value(other);

    return (new(Float, y));
}

static Object *Float_add_float(FloatClass *this, FloatClass *other)
{
    float x = this->x + other->x;

    return (new(Float, x));
}

static Object *Float_sub(FloatClass *this, FloatClass *other)
{
    float x = this->x - other->x;

    return (new(Float, x));
}

static Object *Float_mul(FloatClass *this, FloatClass *other)
{
    float x = this->x * other->x;

    return (new(Float, x));
}

static Object *Float_div(FloatClass *this, FloatClass *other)
{
    float x = this->x / other->x;

    return (new(Float, x));
}

static bool Float_eq(FloatClass *this, FloatClass *other)
{
    return(this->x == other->x);
}

static bool Float_lt(FloatClass *this, FloatClass *other)
{
    return(this->x < other->x);
}

static bool Float_gt(FloatClass *this, FloatClass *other)
{
    return(this->x > other->x);
}

static const FloatClass _description = {
    {   /* Class struct */
        .__size__ = sizeof(FloatClass),
        .__name__ = "Float",
        .__ctor__ = (ctor_t)&Float_ctor,
        .__dtor__ = (dtor_t)&Float_dtor,
        .__str__ = (to_string_t) &Float_to_string,
        .__add__ = (binary_operator_t) &Float_add_type,
        .__sub__ = (binary_operator_t) &Float_sub,
        .__mul__ = (binary_operator_t) &Float_mul,
        .__div__ = (binary_operator_t) &Float_div,
        .__eq__ = (binary_comparator_t) &Float_eq,
        .__gt__ = (binary_comparator_t) &Float_gt,
        .__lt__ = (binary_comparator_t) &Float_lt,
    },
    .x = 0,
};

const Class *Float = (const Class *)&_description;
