/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD05-timothe.coniel
** File description:
** to_int
*/

#include "string.h"

int to_int(const string_t *this)
{
    return (atoi(this->str));
}