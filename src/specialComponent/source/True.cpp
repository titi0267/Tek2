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
    return getState()[0];
}

void nts::True::setLink(size_t pin, nts::IComponent &other, size_t otherPin)
{
    _saveLink.emplace(pin, Link{other, otherPin});
}

void nts::True::simulate(size_t tick)
{
    for (auto itr : _saveLink) {
        setState(itr.first, itr.second.component.compute(itr.second.pin));
    }
}

void nts::True::dump() const
{
}

nts::True::~True()
{
}
