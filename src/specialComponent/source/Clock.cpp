/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Clock
*/

#include "../include/Clock.hpp"

nts::Clock::Clock()
{
    setType("clock");
    _pins.push_back(nts::Tristate::UNDEFINED);
}

nts::Tristate nts::Clock::compute(size_t pin)
{
    return getState()[pin-1];
}

void nts::Clock::setLink(size_t pin, nts::IComponent &other, size_t otherPin)
{
}

void nts::Clock::simulate(size_t tick)
{
}

void nts::Clock::dump() const
{
}

nts::Clock::~Clock()
{
}
