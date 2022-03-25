/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Error
*/

#include "Error.hpp"
#include "../define.hpp"
#include <iostream>

Error::Error()
{
}

Error::~Error()
{
}

std::string Error::getReason() const
{
    return (_reason);
}

int Error::getReturnValue() const
{
    return (_returnValue);
}

void Error::setReturnValue(int returnValue)
{
    _returnValue = returnValue;
}

void Error::setReason(const std::string reason)
{
    _reason = reason;
}

void Error::displayReason() const
{
    std::cerr << getReason() << std::endl;
}

void Error::exitProgram() const
{
    exit(getReturnValue());
}

void Error::checkArgs(int ac, char **av)
{
    if (ac != 2) {
        setReason("ERROR, argument problem.\nPlease use -h to more information.");
        displayReason();
        setReturnValue(ERROR);
        exitProgram();
    }
}