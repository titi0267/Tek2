/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Error
*/

#include "Error.hpp"

Error::Error(char *error)
{
    _error = error;
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

void Error::setError(const char *error)
{
    _error = error;
}
void Error::getError(const char *error)
{
    _error = error;
}

void Error::setReason(const std::string reason)
{
    _reason = reason;
}

void Error::displayReason() const
{
    std::cerr << _reason << std::endl;
}

void Error::exitProgram() const
{
    exit(_returnValue);
}

const char *Error::what()
{
    return _error.c_str();
}

void Error::checkArgs(int ac, char **av)
{
    if (ac == 2 && av[1] == "-h") {
        setReason("USAGE\n\t./arcade graphical_library.so\n\nDESCRIPTION\n\tRunning the core programm using the given library\n");
        displayReason();
        setReturnValue(SUCCESS);
        exitProgram();
    }
    if (ac != 2) {
        setReason("ERROR, argument problem.\nPlease use -h to more information.");
        displayReason();
        setReturnValue(ERROR);
        exitProgram();
    }
}

void Error::exitError(int retValue, const std::string reason)
{
    Error::setReason(reason);
    Error::setReturnValue(retValue);
    Error::displayReason();
    Error::exitProgram();
}