/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Comp4069
*/

#include "../include/Comp4069.hpp"

nts::Comp4069::Comp4069()
{
    setType("4069");
    for (int i = 0; i < 14; i++)
        _pins.push_back(nts::Tristate::UNDEFINED);
}

nts::Tristate nts::Comp4069::compute(size_t pin)
{
    nts::Link *link = _saveLink[pin];

    if (link->component.getType() == "clock") {
        link->component.setState(1, nts::Gates::Not(link->component.getState()[0]));
    }
    switch (pin) {
        case 1:
            setState(pin, link->component.compute(link->pin));
            break;
        case 2:
            setState(pin, nts::Gates::Not(compute(1)));
            break;
        case 3:
            setState(pin, link->component.compute(link->pin));
            break;
        case 4:
            setState(pin, nts::Gates::Not(compute(3)));
            break;
        case 5:
            setState(pin, link->component.compute(link->pin));
            break;
        case 6:
            setState(pin, nts::Gates::Not(compute(5)));
            break;
        case 8:
            setState(pin, nts::Gates::Not(compute(9)));
            break;
        case 9:
            setState(pin, link->component.compute(link->pin));
            break;
        case 10:
            setState(pin, nts::Gates::Not(compute(11)));
            break;
        case 11:
            setState(pin, link->component.compute(link->pin));
            break;
        case 12:
            setState(pin, nts::Gates::Not(compute(13)));
            break;
        case 13:
            setState(pin, link->component.compute(link->pin));
            break;
        default:
            break;
    }
    return getState()[pin-1];
}

void nts::Comp4069::setLink(size_t pin, nts::IComponent &other, size_t otherPin)
{
    nts::Link *link = new nts::Link{other, otherPin};

    _saveLink.emplace(pin, link);
}

void nts::Comp4069::simulate(size_t tick)
{
    for (auto itr : _saveLink) {
        setState(itr.first, itr.second->component.compute(itr.second->pin));
    }
}

void nts::Comp4069::dump() const
{
}

nts::Comp4069::~Comp4069()
{
}
