/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Components
*/

#include "../include/Components.hpp"

nts::Components::Components()
{
}

/*std::vector<nts::Tristate> create4081()
{
    return Comp4081::compute(...);
}
*/

void nts::Components::setName(std::string name)
{
    _compName = name;
}

std::string nts::Components::getName() const
{
    return _compName;
}

nts::Components::~Components()
{
}
