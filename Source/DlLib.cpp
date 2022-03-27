/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** DlLib
*/

#include "DlLib.hpp"
#include "define.hpp"
#include <dlfcn.h>
#include <iostream>

DlLib::DlLib()
{
}

DlLib::~DlLib()
{
}

void DlLib::open(char *str)
{
    std::string error = "ERROR: couldn't open library";

    _open = dlopen(str, RTLD_LAZY);
    if (!_open) {
        _setError.setReason(error);
        _setError.displayReason();
        _setError.setReturnValue(ERROR);
        _setError.exitProgram();
    }
    *(void **)(&_about) = dlsym(_open, "about");
}

void DlLib::close()
{
    dlclose(_open);
}
