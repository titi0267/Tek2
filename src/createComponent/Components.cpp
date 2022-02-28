/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Components
*/

#include "../../include/Components.hpp"

Components::Components()
{
}

std::vector<nts::Tristate> create4081()
{
    return Comp4081::compute(...);
}

Components::~Components()
{
}
