/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Comp4001
*/

#include "../include/Comp4001.hpp"

nts::Comp4001::Comp4001()
{
    setType("4001");
    for (int i = 0; i < 14; i++)
        _pins.push_back(nts::Tristate::UNDEFINED);
}

nts::Tristate nts::Comp4001::compute(size_t pin)
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
            setState(pin, link->component.compute(link->pin));
            break;
        case 3:
            setState(pin, nts::Gates::Not(nts::Gates::Or(compute(1), compute(2))));
            break;
        case 4:
            setState(pin, nts::Gates::Not(nts::Gates::Or(compute(5), compute(6))));
            break;
        case 5:
            setState(pin, link->component.compute(link->pin));
            break;
        case 6:
            setState(pin, link->component.compute(link->pin));
            break;
        case 8:
            setState(pin, link->component.compute(link->pin));
            break;
        case 9:
            setState(pin, link->component.compute(link->pin));
            break;
        case 10:
            setState(pin, nts::Gates::Not(nts::Gates::Or(compute(8), compute(9))));
            break;
        case 11:
            setState(pin, nts::Gates::Not(nts::Gates::Or(compute(12), compute(13))));
            break;
        case 12:
            setState(pin, link->component.compute(link->pin));
            break;
        case 13:
            setState(pin, link->component.compute(link->pin));
            break;
        default:
            break;
    }

    return getState()[pin-1];
}

void nts::Comp4001::setLink(size_t pin, nts::IComponent &other, size_t otherPin)
{
    nts::Link *link = new nts::Link{other, otherPin};

    _saveLink.emplace(pin, link);
}

void nts::Comp4001::simulate(size_t tick)
{
}

void nts::Comp4001::dump() const
{
}


nts::Comp4001::~Comp4001()
{
}