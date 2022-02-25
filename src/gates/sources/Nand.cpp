/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Nand
*/

#include "../include/Nand.hpp"

Nand::Nand()
{
}

nts::Tristate Nand::getNand(nts::Tristate a, nts::Tristate b)
{
    nts::Tristate TRUE = nts::Tristate::TRUE;
    nts::Tristate FALSE = nts::Tristate::FALSE;
    nts::Tristate UNDEFINED = nts::Tristate::UNDEFINED;

    if ((a == TRUE && b == UNDEFINED) || (a == UNDEFINED && b == TRUE))
        return UNDEFINED;
    if ((a == TRUE && b == TRUE))
        return FALSE;
    return TRUE;
}

Nand::~Nand()
{
}
