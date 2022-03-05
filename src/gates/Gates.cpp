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

nts::Tristate Not(nts::Tristate a)
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

nts::Tristate Xor(nts::Tristate a, nts::Tristate b)
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

nts::Tristate Nand(nts::Tristate a, nts::Tristate b)
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

nts::Tristate Or(nts::Tristate a, nts::Tristate b)
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

nts::Tristate Nor(nts::Tristate a, nts::Tristate b)
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
