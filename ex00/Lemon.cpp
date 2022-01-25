/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD10am-timothe.coniel
** File description:
** Lemon
*/

#include "Lemon.hpp"

Lemon::Lemon() : Fruit(_fruit, _vitamins)
{
    _fruit = "lemon";
    _vitamins = 3;
}

Lemon::~Lemon()
{
}
