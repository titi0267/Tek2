/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Or
*/

#include "../include/Or.hpp"

Or::Or()
{
}

nts::Tristate getOr(nts::Tristate a, nts::Tristate b)
{
    nts::Tristate TRUE = nts::Tristate::TRUE;
    nts::Tristate FALSE = nts::Tristate::FALSE;
    nts::Tristate UNDEFINED = nts::Tristate::UNDEFINED;

    if ((a == UNDEFINED && b == UNDEFINED))
        return UNDEFINED;
    else if ((a == FALSE && b == FALSE))
        return FALSE;
    return TRUE;
}

Or::~Or()
{
}
