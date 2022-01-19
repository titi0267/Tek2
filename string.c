/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGRUSH2-timothe.coniel
** File description:
** string
*/

#include <stdlib.h>
#include <stdarg.h>
#include "raise.h"
#include "string.h"
#include "new.h"

typedef struct
{
    Class       base;
    size_t _size;
    char *_str;
}   StringClass;

static char *String_to_string(StringClass *this)
{
    char *str = malloc(sizeof(char) * (this->_size + 12));

    if (str == NULL)
        raise("Out of memory");
    snprintf(str, this->_size + 11, "<String (%s)>", this->_str);
    return (str);
}

static Object *String_add(StringClass *this, StringClass *other)
{
    char *str = malloc(sizeof(char) * (other->_size + this->_size + 1));

    if (str == NULL)
        raise("Out of memory");
    strcpy(str, this->_str);
    strcat(str, other->_str);
    return (new(String, str));
}

static void String_set_values(StringClass *this, char *str, int size)
{
    this->_str = str;
    this->_size = size;
}

static bool Strcmp(StringClass *this, StringClass *other)
{
    return (this->_size == other->_size);
}

static bool Strgt(StringClass *this, StringClass *other)
{
    return (this->_size > other->_size);
}

static bool Strlt(StringClass *this, StringClass *other)
{
    return (this->_size < other->_size);
}

static void String_ctor(StringClass *this, va_list *args)
{
    char *str = va_arg(*args, char *);
    int size = strlen(str);

    String_set_values(this, strdup(str), size);
}

static void String_dtor(StringClass *this)
{
    free(this->_str);
}

static const StringClass   _descr = {
    {   /* Class struct */
        .__size__ = sizeof(StringClass),
        .__name__ = "String",
        .__ctor__ = (ctor_t)&String_ctor,
        .__dtor__ = (dtor_t)&String_dtor,
        .__str__ = (to_string_t)&String_to_string,
        .__add__ = (binary_operator_t)&String_add,
        .__sub__ = NULL,
        .__mul__ = NULL,
        .__div__ = NULL,
        .__eq__ = (binary_comparator_t)&Strcmp,
        .__gt__ = (binary_comparator_t)&Strgt,
        .__lt__ = (binary_comparator_t)&Strlt,
    },
    ._size = 0,
    ._str = NULL,
};

const Class   *String = (const Class *)&_descr;

