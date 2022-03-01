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
    switch (pin)
    {
        case 3:
            return And(_pins[0], _pins[1]);
        case 4:
            return And(_pins[2], _pins[3]);
        case 10:
            return And(_pins[4], _pins[5]);
        case 11:
            return And(_pins[6], _pins[7]);
    }
}

Comp4081::~Comp4081()
{
}
