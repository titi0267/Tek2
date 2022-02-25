/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** 4081And
*/

#pragma once

#include "../include/Components.hpp"
#include "../include/Gates.hpp"

class Comp4081 : public Components
{
    public:
        Comp4081();
        nts::Tristate compute(size_t pin);
        ~Comp4081();

    private:
};
