/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Error
*/

#include "Error.hpp"

Error::Error(std::string message)
{
    _message = message;
}

Error::~Error()
{
    ;
}

const char *Error::what()
{
    return _message.c_str();
}
