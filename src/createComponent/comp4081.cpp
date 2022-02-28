/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** 4081And
*/

#include "comp4081.hpp"

Comp4081::Comp4081(std::vector<nts::Tristate> pins[7])
{
    for (int i = 0; i < 8; i++)
        Comp4081::pins[i] = pins[i];
}

nts::Tristate Comp4081::compute(size_t pin)
{
    switch (pin)
    {
        case 3:
            return andGate.getAnd(Comp4081::pins[0], Comp4081::pins[1]);
        case 4:
            return andGate.getAnd(Comp4081::pins[2], Comp4081::pins[3]);
        case 10:
            return andGate.getAnd(Comp4081::pins[4], Comp4081::pins[5]);
        case 11:
            return andGate.getAnd(Comp4081::pins[6], Comp4081::pins[7]);
    }
}

Comp4081::~Comp4081()
{
}
