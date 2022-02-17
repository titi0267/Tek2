/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Icomponents
*/

#include "Icomponent.hpp"

nts::IComponent::~IComponent()
{
    ;
}

void nts::IComponent::simulate(size_t tick)
{
    ;
}

nts::Tristate nts::IComponent::compute(size_t pin)
{
    return UNDEFINED;
}

void nts::IComponent::setLink(size_t pin, nts::IComponent &other,size_t otherPin)
{
    ;
}

void nts::IComponent::dump() const
{
    ;
}