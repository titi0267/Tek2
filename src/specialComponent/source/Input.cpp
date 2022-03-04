/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Input
*/

#include "../include/Input.hpp"

nts::Input::Input(int compNumber, const std::string &name)
{
    setComp(name, "input");
    _pins.push_back(nts::Tristate::UNDEFINED);
    for (auto itr : _pins)
        std::cout << itr << std::endl;
    std::cout << "oui" << std::endl;
    //_pin.setPin(key, nts::Tristate::UNDEFINED);
    //setName(name);
}

nts::Tristate nts::Input::compute(size_t pin)
{
    return getState()[0];
}

void nts::Input::simulate(size_t tick)
{
    ;
}

void nts::Input::dump() const
{
    //std::cout << "Input(s):" << std::endl << "  " << getName() << ": " << _pin.getPin(0) << std::endl;
}

nts::Input::~Input()
{
}
