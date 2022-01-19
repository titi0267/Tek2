/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGRUSH2-timothe.coniel
** File description:
** list
*/

#include <stdlib.h>
#include <stdarg.h>
#include "raise.h"
#include "list.h"
#include "new.h"

typedef struct ListNode_s {
    Object *data;
    struct ListNode_s *next;
    struct ListNode_s *prev;
} ListNode;

typedef struct
{
    Container   base;
    Class       *_type;
    size_t      _size;
    ListNode    *_list_start;
    ListNode    *_list_end;
    push_front_t push_front;
    push_back_t push_back;
    pop_front_t pop_front;
    pop_back_t pop_back;
} ListClass;

typedef struct {
    Iterator base;
    ListClass *_list;
    size_t _idx;
} ListIteratorClass;

static void List_add_at_front(ListClass *this, Object *obj);
static void List_add_at_back(ListClass *this, Object *obj);
static void List_add_at_position(ListClass *this, Object *obj, size_t pos);

static void List_del_at_front(ListClass *this);
static void List_del_at_back(ListClass *this);
static void List_del_at_position(ListClass *this, size_t pos);

static Object *List_get_at_pos(ListClass *this, size_t pos);
static void List_set_at_pos(ListClass *this, Object *obj, size_t pos);

static void ListIterator_ctor(ListIteratorClass *this, va_list *args)
{
    this->_list = va_arg(*args, ListClass*);
    this->_idx = va_arg(*args, int);
}

static bool ListIterator_eq(ListIteratorClass *this, ListIteratorClass *other)
{
    return (this->_idx == other->_idx);
}

static bool ListIterator_gt(ListIteratorClass *this, ListIteratorClass *other)
{
    return (this->_idx > other->_idx);
}

static bool ListIterator_lt(ListIteratorClass *this, ListIteratorClass *other)
{
    return (this->_idx < other->_idx);
}

static void ListIterator_incr(ListIteratorClass *this)
{
    this->_idx += 1;
}

static Object *ListIterator_getval(ListIteratorClass *this)
{
    if (this->_idx >= this->_list->_size)
        raise("Out of range");
    return (List_get_at_pos(this->_list, this->_idx));
}

static void ListIterator_setval(ListIteratorClass *this, ...)
{
    va_list args;

    va_start(args, this);
    if (this->_idx >= this->_list->_size)
        raise("Out of memory bounds");
    List_set_at_pos(this->_list, va_new(this->_list->_type, &args), this->_idx);
    va_end(args);
}

static const ListIteratorClass ListIteratorDescr = {
    {   /* Iterator struct */
        {   /* Class struct */
            .__size__ = sizeof(ListIteratorClass),
            .__name__ = "ListIterator",
            .__ctor__ = (ctor_t)&ListIterator_ctor,
            .__dtor__ = NULL,
            .__str__ = NULL,
            .__add__ = NULL,
            .__sub__ = NULL,
            .__mul__ = NULL,
            .__div__ = NULL,
            .__eq__ = (binary_comparator_t)&ListIterator_eq,
            .__gt__ = (binary_comparator_t)&ListIterator_gt,
            .__lt__ = (binary_comparator_t)&ListIterator_lt,
        },
        .__incr__ = (incr_t)&ListIterator_incr,
        .__getval__ = (getval_t)&ListIterator_getval,
        .__setval__ = (setval_t)&ListIterator_setval,
    },
    ._list = NULL,
    ._idx = 0
};

static const Class *ListIterator = (const Class *)&ListIteratorDescr;


static void List_ctor(ListClass *this, va_list *args)
{
    size_t size = va_arg(*args, size_t);
    Class *type = va_arg(*args, Class*);
    va_list args_cpy;

    this->_size = 0;
    this->_type = type;
    va_copy(args_cpy, *args);
    for (size_t i = 0; i < size; i++) {
        List_add_at_back(this, va_new(type, args));
        va_copy(*args, args_cpy);
    }
}

static void List_dtor(ListClass *this)
{
    ListNode *next = NULL;

    for (ListNode *cpy = this->_list_start; cpy; cpy = next) {
        next = cpy->next;
        delete(cpy->data);
        free(cpy);
    }
}

static size_t List_len(ListClass *this)
{
    return (this->_size);
}

static Iterator *List_begin(ListClass *this)
{
    return (new(ListIterator, this, 0));
}

static Iterator *List_end(ListClass *this)
{
    return (new(ListIterator, this, this->_size));
}

static void List_add_at_front(ListClass *this, Object *obj)
{
    ListNode *node = malloc(sizeof(ListNode));

    if (!node)
        raise("Out of memory");
    node->data = obj;
    node->next = this->_list_start;
    node->prev = NULL;
    if (this->_list_start != NULL)
        this->_list_start->prev = node;
    this->_list_start = node;
    if (this->_list_end == NULL)
        this->_list_end = node;
    this->_size += 1;
}

static void List_add_at_back(ListClass *this, Object *obj)
{
    ListNode *node = malloc(sizeof(ListNode));

    if (!node)
        raise("Out of memory");
    node->data = obj;
    node->next = NULL;
    node->prev = this->_list_end;
    if (this->_list_end != NULL)
        this->_list_end->next = node;
    this->_list_end = node;
    if (this->_list_start == NULL)
        this->_list_start = node;
    this->_size += 1;
}

static void List_add_at_position(ListClass *this, Object *obj, size_t pos)
{
    ListNode *node = malloc(sizeof(ListNode));
    ListNode *prev = NULL;
    ListNode *next = this->_list_start;

    if (!node)
        raise("Out of memory");
    node->data = obj;
    for (; pos > 0 && next; pos--, prev = next, next = next->next);
    if (pos > 0)
        raise("Invalid position");
    if (prev)
        prev->next = node;
    else
        this->_list_start = node;
    if (next)
        next->prev = node;
    else
        this->_list_end = node;
    node->prev = prev;
    node->next = next;
    this->_size += 1;
}

static void List_del_at_front(ListClass *this)
{
    ListNode *front = this->_list_start;

    if (!front)
        return;
    if (front->next) {
        front->prev = NULL;
        this->_list_start = front->next;
    }
    this->_size -= 1;
    delete(front->data);
    free(front);
}

static void List_del_at_back(ListClass *this)
{
    ListNode * back = this->_list_end;

    if (!back)
        return;
    if (back->prev) {
        back->next = NULL;
        this->_list_end = back->prev;
    }
    this->_size -= 1;
    delete(back->data);
    free(back);
}

static void List_del_at_position(ListClass *this, size_t pos)
{
    ListNode *node = this->_list_start;
    ListNode *prev = NULL;
    ListNode *next = NULL;

    for (; pos > 0 && node; pos--, node = node->next);
    if (pos > 0 || !node)
        raise("Invalid position");
    prev = node->prev;
    next = node->next;
    if (prev == NULL)
        List_del_at_front(this);
    else if (next == NULL)
        List_del_at_back(this);
    else {
        this->_size -= 1;
        next->prev = prev;
        prev->next = next;
        delete(node->data);
        free(node);
    }
}

static Object *List_get_at_pos(ListClass *this, size_t pos)
{
    ListNode *node = this->_list_start;

    for (; pos > 0 && node; pos--, node = node->next);
    if (pos > 0 || !node)
        raise("Invalid position");
    return (node->data);
}

static void List_set_at_pos(ListClass *this, Object *obj, size_t pos)
{
    List_del_at_position(this, pos);
    List_add_at_position(this, obj, pos);
}

static Object *List_getitem(ListClass *this, ...)
{
    va_list args;
    size_t index;

    va_start(args, this);
    index = va_arg(args, size_t);
    if (index >= this->_size)
        raise("Out of bounds memory");
    va_end(args);
    return (List_get_at_pos(this, index));
}

static void List_setitem(ListClass *this, ...)
{
    va_list args;
    size_t index;

    va_start(args, this);
    index = va_arg(args, size_t);
    if (index >= this->_size)
        raise("Out of bounds memory");
    List_set_at_pos(this, va_new(this->_type, &args), index);
    va_end(args);
}

static const ListClass _descr = {
    {   /* Container struct */
        {   /* Class struct */
            .__size__ = sizeof(ListClass),
            .__name__ = "List",
            .__ctor__ = (ctor_t)&List_ctor,
            .__dtor__ = (dtor_t)&List_dtor,
            .__str__ = NULL,
            .__add__ = NULL,
            .__sub__ = NULL,
            .__mul__ = NULL,
            .__div__ = NULL,
            .__eq__ = NULL,
            .__gt__ = NULL,
            .__lt__ = NULL,
        },
        .__len__ = (len_t)&List_len,
        .__begin__ = (iter_t)&List_begin,
        .__end__ = (iter_t)&List_end,
        .__getitem__ = (getitem_t)&List_getitem,
        .__setitem__ = (setitem_t)&List_setitem,
    },
    ._type = NULL,
    ._size = 0,
    ._list_start = NULL,
    ._list_end = NULL,
    .push_front = (push_front_t) &List_add_at_front,
    .push_back = (push_back_t) &List_add_at_back,
    .pop_front = (pop_front_t) &List_del_at_front,
    .pop_back = (pop_back_t) &List_del_at_back,
};

const Class *List = (const Class*) &_descr;

