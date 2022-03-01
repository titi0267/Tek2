/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Input
*/

#include "../include/Input.hpp"

nts::Input::Input(size_t key)
{
    _pin.setPin(key, nts::Tristate::UNDEFINED);
}

nts::Tristate nts::Input::compute(size_t pin)
{
    return _pin.getPin(pin);
}

nts::Input::~Input()
{
}
