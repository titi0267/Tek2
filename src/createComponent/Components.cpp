/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Components
*/

#include "../include/Components.hpp"
#include "../specialComponent/include/Input.hpp"
#include "../specialComponent/include/Output.hpp"

nts::Components::Components()
{
}

void nts::Components::setType(std::string type)
{
    _type = type;
}

std::string &nts::Components::getType()
{
    return _type;
}

void nts::Components::setLink(size_t pin, nts::IComponent &other, size_t otherPin)
{
    ;
}

std::vector<nts::Tristate> &nts::Components::getState()
{
    return _pins;
}

void nts::Components::setState(size_t pin, nts::Tristate state)
{
    _pins[pin - 1] = state;
}

nts::Tristate nts::Components::compute(size_t pin)
{
    return nts::UNDEFINED;
}

/*std::map<size_t, nts::Link *> &nts::Components::getLink()
{
    return _saveLink;
}*/

void nts::Components::simulate(size_t tick)
{
}

void nts::Components::dump() const
{
    ;
}



nts::Components::~Components()
{
}
