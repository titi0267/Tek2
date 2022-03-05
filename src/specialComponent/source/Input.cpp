/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Input
*/

#include "../include/Input.hpp"

nts::Input::Input()
{
    setType("input");
    _pins.push_back(nts::Tristate::UNDEFINED);
}

nts::Tristate nts::Input::compute(size_t pin)
{
    return getState()[0];
}

void nts::Input::simulate(size_t tick)
{
}

void nts::Input::dump() const
{
}

nts::Input::~Input()
{
}
