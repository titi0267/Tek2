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

nts::Tristate getAnd(std::vector<nts::Tristate> a, std::vector<nts::Tristate> b)
{
    nts::Tristate TRUE = nts::Tristate::TRUE;
    nts::Tristate FALSE = nts::Tristate::FALSE;
    nts::Tristate UNDEFINED = nts::Tristate::UNDEFINED;


    if ((a[0] == TRUE && b[0] == TRUE))
        return TRUE;
    else if ((a[0] == UNDEFINED && b[0] == TRUE) || (a[0] == TRUE && b[0] == UNDEFINED))
        return UNDEFINED;
    return FALSE;
}

And::~And()
{
}
