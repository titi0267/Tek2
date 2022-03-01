/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Output
*/

#include "../include/Output.hpp"

nts::Output::Output(size_t key, std::string name)
{
    _pin.setPin(key, nts::Tristate::UNDEFINED);
    setName(name);
}

nts::Tristate nts::Output::compute(size_t pin)
{
    return _pin.getPin(pin);
}

void nts::Output::dump() const
{
    std::cout << "Output(s):" << std::endl << "  " << getName() << ": " << _pin.getPin(0) << std::endl;
}

nts::Output::~Output()
{
}
