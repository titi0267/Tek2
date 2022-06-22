/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** False
*/

#include "../include/False.hpp"

nts::False::False()
{
    setType("false");
    _pins.push_back(nts::Tristate::FALSE);
}

nts::Tristate nts::False::compute(size_t pin)
{
    return getState()[pin-1];
}

void nts::False::setLink(size_t pin, nts::IComponent &other, size_t otherPin)
{
}

void nts::False::simulate(size_t tick)
{
}

void nts::False::dump() const
{
}

nts::False::~False()
{
}
