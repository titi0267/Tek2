/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Pins
*/

#pragma once
#include "../include/IComponent.hpp"

class Pins {
    public:
        Pins();
        nts::Tristate setPin(size_t pin, nts::Tristate a);
        ~Pins();

    protected:
    private:
};
