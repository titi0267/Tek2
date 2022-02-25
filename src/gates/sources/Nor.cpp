/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Nor
*/

#include "../include/Nor.hpp"

Nor::Nor()
{
}

nts::Tristate getNor(nts::Tristate a, nts::Tristate b)
{
    nts::Tristate TRUE = nts::Tristate::TRUE;
    nts::Tristate FALSE = nts::Tristate::FALSE;
    nts::Tristate UNDEFINED = nts::Tristate::UNDEFINED;

    if ((a == FALSE && b == FALSE))
        return TRUE;
    if ((a == FALSE && b == UNDEFINED) || (a == UNDEFINED && b == FALSE))
        return UNDEFINED;
    return FALSE;
}

Nor::~Nor()
{
}
