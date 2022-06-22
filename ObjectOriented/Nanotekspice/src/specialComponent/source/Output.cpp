/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Output
*/

#include "../include/Output.hpp"

nts::Output::Output()
{
    setType("output");
    _pins.push_back(nts::Tristate::UNDEFINED);
}

nts::Tristate nts::Output::compute(size_t pin)
{
    nts::Link *link = _saveLink[pin];

    if (link->component.getType() == "clock") {
        link->component.setState(1, nts::Gates::Not(link->component.getState()[0]));
    }
    setState(pin, link->component.compute(link->pin));
    return getState()[pin-1];
}

void nts::Output::setLink(size_t pin, nts::IComponent &other, size_t otherPin)
{
    nts::Link *link = new nts::Link(other, otherPin);

    if (other.getType() == "true") {
        setState(1, nts::Tristate::TRUE);
    } else if (other.getType() == "false") {
        setState(1, nts::Tristate::FALSE);
    }
    _saveLink.emplace(pin, link);
}

void nts::Output::simulate(size_t tick)
{
}

void nts::Output::dump() const
{
}

nts::Output::~Output()
{
}
