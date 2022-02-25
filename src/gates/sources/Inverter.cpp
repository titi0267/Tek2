/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Inverter
*/

#include "../include/Inverter.hpp"

/*********************/
/*                   */
/*     Not Gate      */
/*                   */
/*********************/

Inverter::Inverter()
{
}

nts::Tristate Inverter::getInverter(nts::Tristate a)
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


Inverter::~Inverter()
{
}
