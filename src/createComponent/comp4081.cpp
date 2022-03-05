/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** 4081And
*/

#include "comp4081.hpp"
#include "../gates/Gates.hpp"

nts::Comp4081::Comp4081(std::vector<nts::Tristate> pins) : _pins(pins)
{
    for (int i = 0; i < 8; i++)
        _pins[i] = pins[i];
}

nts::Tristate nts::Comp4081::compute(size_t pin)
{
    _pins[2] = nts::Gates::And(_pins[0], _pins[1]);
    _pins[3] = nts::Gates::And(_pins[4], _pins[5]);
    _pins[9] = nts::Gates::And(_pins[7], _pins[8]);
    _pins[10] = nts::Gates::And(_pins[11], _pins[12]);
    return _pins[pin - 1];
}

nts::Comp4081::~Comp4081()
{
}
