/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD10am-timothe.coniel
** File description:
** Fruit
*/

#include "Fruit.hpp"

Fruit::Fruit(const std::string &name, int vitamins)
    : _fruit(name), _vitamins(vitamins)
{
}

Fruit::~Fruit()
{
}

std::string Fruit::getName()
{
    return _fruit;
}

int Fruit::getVitamins()
{
    return _vitamins;
}
