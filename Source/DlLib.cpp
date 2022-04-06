/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** DlLib
*/

#include "DlLib.hpp"
#include "define.hpp"
#include <iostream>

DlLib::DlLib(char *libName)
{
    open(libName);
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
}

std::unique_ptr<IDisplayModule> DlLib::getLib()
{
    *(void **)(&_lib) = dlsym(_open, "gEpitechArcadeGetDisplayModuleHandle");

    //_lib->;
    //return std::make_unique<IDisplayModule>();
}

std::unique_ptr<IGameModule> DlLib::getGame()
{
    *(void **)(&_game) = dlsym(_open, "gEpitechArcadeGetGameModuleHandle");

    //return (_game);
}

void DlLib::close()
{
    dlclose(_open);
}
