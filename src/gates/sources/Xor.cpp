/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Xor
*/

#include "../include/Xor.hpp"

Xor::Xor()
{
}

nts::Tristate Xor::getXor(nts::Tristate a, nts::Tristate b)
{
    nts::Tristate TRUE = nts::Tristate::TRUE;
    nts::Tristate FALSE = nts::Tristate::FALSE;
    nts::Tristate UNDEFINED = nts::Tristate::UNDEFINED;

    if ((a == TRUE && b == FALSE) || (a == FALSE && b == TRUE) ||
        (a == UNDEFINED && b == TRUE) ||
        (a == TRUE && b == UNDEFINED))
        return TRUE;
    else if ((a == FALSE && b == FALSE) || (a == TRUE && b == TRUE))
        return FALSE;
    return UNDEFINED;
}

Xor::~Xor()
{
}
