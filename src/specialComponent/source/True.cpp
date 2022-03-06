/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** True
*/

#include "../include/True.hpp"

nts::True::True()
{
    setType("true");
    _pins.push_back(nts::Tristate::TRUE);
}

nts::Tristate nts::True::compute(size_t pin)
{
    return getState()[pin-1];
}

void nts::True::setLink(size_t pin, nts::IComponent &other, size_t otherPin)
{
    nts::Link *link = new nts::Link{other, otherPin};

    _saveLink.emplace(pin, link);
}

void nts::True::simulate(size_t tick)
{
}

void nts::True::dump() const
{
}

nts::True::~True()
{
}
