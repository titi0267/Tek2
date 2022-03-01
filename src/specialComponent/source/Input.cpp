/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Input
*/

#include "../include/Input.hpp"

nts::Input::Input(size_t key, std::string name)
{
    _pin.setPin(key, nts::Tristate::UNDEFINED);
    setName(name);
}

nts::Tristate nts::Input::compute(size_t pin)
{
    return _pin.getPin(pin);
}

void nts::Input::dump() const
{
    std::cout << "Input(s):" << std::endl << "  " << getName() << ": " << _pin.getPin(0) << std::endl;
}

nts::Input::~Input()
{
}
