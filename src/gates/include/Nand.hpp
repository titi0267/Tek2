/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Nand
*/

#pragma once
#include "../../include/IComponent.hpp"

class Nand {
    public:
        Nand();
        nts::Tristate Nand::getNand(nts::Tristate a, nts::Tristate b);
        ~Nand();

    protected:
    private:
};
