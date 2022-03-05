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
    nts::Link *link = _saveLink[1];

    _pins[0] = link->component.compute(link->pin);
    return _pins[0];
}

void nts::Output::setLink(size_t pin, nts::IComponent &other, size_t otherPin)
{
    /*
    if (other.getType() == "true") {
        setState(1, nts::Tristate::TRUE);
    } else if (other.getType() == "false") {
        setState(1, nts::Tristate::FALSE);
    }*/
    nts::Link *link = new nts::Link(other, otherPin);
    _saveLink.emplace(pin, link);
}

void nts::Output::simulate(size_t tick)
{
    std::cout << "SIMULATE" << std::endl;
    for (auto itr : _saveLink) {
        setState(itr.first, itr.second->component.compute(itr.second->pin));
    }
}

void nts::Output::dump() const
{
}

nts::Output::~Output()
{
}
