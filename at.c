/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD05-timothe.coniel
** File description:
** at
*/

#include "string.h"

char at(const string_t * this, size_t pos)
{
    if (this != NULL && this->str != NULL) {
        if (pos + 1 > strlen(this->str)) {
            return (-1);
        } else if (pos < 0)
            return (-1);
        return (this->str[pos]);
    }
    return (-1);
}