/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Link
*/

#include "../include/Link.hpp"

nts::Link::Link(IComponent &comp, size_t p) : component(comp), pin(p)
{
}

nts::Link::~Link()
{
}
