/*
** EPITECH PROJECT, 2021
** Paradigms Seminar
** File description:
** Exercice 01
*/

#pragma once

#include <stdarg.h>
#include "object.h"

Object  *new(const Class *class, ...);
Object  *va_new(const Class *class, va_list* ap);
void    delete(Object *ptr);
