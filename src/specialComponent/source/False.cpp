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
    return getState()[0];
}

void nts::False::setLink(size_t pin, nts::IComponent &other, size_t otherPin)
{
    nts::Link *link = new nts::Link{other, otherPin};

    _saveLink.emplace(pin, link);
}

void nts::False::simulate(size_t tick)
{
    for (auto itr : _saveLink) {
        setState(itr.first, itr.second->component.compute(itr.second->pin));
    }
}

void nts::False::dump() const
{
}

nts::False::~False()
{
}
