/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Xor
*/

#pragma once
#include "../../include/IComponent.hpp"

class Xor
{
    public:
        Xor();
        nts::Tristate getXor(nts::Tristate a, nts::Tristate b);
        ~Xor();

    protected:
    private:
};
