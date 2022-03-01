/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Pins
*/

#include "Pins.hpp"

nts::Pins::Pins()
{
}

nts::Tristate nts::Pins::getPin(std::size_t key)
{
    std::map<std::size_t, nts::Tristate>::iterator itr;
    std::cout << std::endl << "The map itr is :" << std::endl;
    std::cout << "\tKEY\tELEMENT\n";
    for (itr = nts::Pins::_pin.begin(); itr != _pin.end() || itr->first == key; ++itr) {
        std::cout << '\t' << itr->first << '\t' << itr->second << std::endl;
    }
    if (itr == _pin.end())
        std::cerr << "Unknown key" << std::endl;
    return itr->second;
}

void nts::Pins::setPin(std::size_t key, nts::Tristate state)
{
    _pin.insert(std::pair<std::size_t, nts::Tristate>(key, state));
}

nts::Pins::~Pins()
{
}
