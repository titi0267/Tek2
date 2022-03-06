/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Gates
*/

#include "Gates.hpp"

nts::Tristate nts::Gates::And(nts::Tristate a, nts::Tristate b)
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

nts::Tristate nts::Gates::Not(nts::Tristate a)
{
    nts::Tristate TRUE = nts::Tristate::TRUE;
    nts::Tristate FALSE = nts::Tristate::FALSE;
    nts::Tristate UNDEFINED = nts::Tristate::UNDEFINED;

    if (a == TRUE)
        return FALSE;
    if (a == FALSE)
        return TRUE;
    return UNDEFINED;
}

nts::Tristate nts::Gates::Xor(nts::Tristate a, nts::Tristate b)
{
    nts::Tristate TRUE = nts::Tristate::TRUE;
    nts::Tristate FALSE = nts::Tristate::FALSE;
    nts::Tristate UNDEFINED = nts::Tristate::UNDEFINED;

    if (a == UNDEFINED || b == UNDEFINED)
        return UNDEFINED;
    if ((a == TRUE && b == TRUE) || (a == FALSE && b == FALSE))
        return FALSE;
    return TRUE;
}

nts::Tristate nts::Gates::Or(nts::Tristate a, nts::Tristate b)
{
    nts::Tristate TRUE = nts::Tristate::TRUE;
    nts::Tristate FALSE = nts::Tristate::FALSE;
    nts::Tristate UNDEFINED = nts::Tristate::UNDEFINED;

    if ((a == FALSE && b == FALSE))
       return FALSE;
    else if ((a == TRUE && (b == TRUE || b == FALSE || b == UNDEFINED)) || (b == TRUE && (a == TRUE || a == FALSE || a == UNDEFINED)))
        return TRUE;
    return UNDEFINED;
}
