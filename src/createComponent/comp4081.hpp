/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** 4081And
*/

#pragma once

#include "../include/IComponent.hpp"
#include "../include/Gates.hpp"

class Comp4081 : public Components, public And
{
    public:
        Comp4081(std::vector<nts::Tristate> pins[7]);
        nts::Tristate compute(size_t pin);
        ~Comp4081();

    protected:
        std::vector<nts::Tristate> pins[7];
        And andGate;

    private:
};
