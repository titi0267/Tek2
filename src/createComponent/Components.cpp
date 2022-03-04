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

void nts::Components::setComp(std::string compName, std::string type)
{
    _name = compName;
    _type = type;
    //_saveComp.insert(std::pair<std::string, int>(compName, compNumber));
}

std::string nts::Components::getType() const
{
    return _type;
}

void nts::Components::setTick(size_t tick)
{
    _tick += tick;
}

size_t nts::Components::getTick() const
{
    return _tick;
}

std::string nts::Components::getComp() const
{
    return _name;
}

void nts::Components::setLink(size_t pin, nts::IComponent &other, size_t otherPin)
{
    ;
}

std::vector<nts::Tristate> nts::Components::getState() const
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

void nts::Components::simulate(size_t tick)
{
//    setTick(tick);
    
}

void nts::Components::dump() const
{
    ;
}



nts::Components::~Components()
{
}
