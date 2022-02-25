/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** And
*/

#include "../include/And.hpp"

And::And()
{
}

nts::Tristate getAnd(nts::Tristate a, nts::Tristate b)
{
    nts::Tristate TRUE = nts::Tristate::TRUE;
    nts::Tristate FALSE = nts::Tristate::FALSE;
    nts::Tristate UNDEFINED = nts::Tristate::UNDEFINED;

    if ((a == TRUE && b == TRUE))
        return TRUE;
    else if ((a == UNDEFINED && b == TRUE) || (a == TRUE && b == UNDEFINED))
        return UNDEFINED;
    return FALSE;
}

And::~And()
{
}
