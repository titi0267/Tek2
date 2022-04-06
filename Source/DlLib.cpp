/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** DlLib
*/

#include "DlLib.hpp"
#include "define.hpp"
#include <iostream>

DlLib::DlLib(char *libName, char *gameName)
{
    openLib(libName);
    openGame(gameName);
}

DlLib::~DlLib()
{
}

void DlLib::openLib(char *str)
{
    std::string error = "ERROR: couldn't open library";

    _openLib = dlopen(str, RTLD_LAZY);
    if (!_openLib) {
        _setError.setReason(error);
        _setError.displayReason();
        _setError.setReturnValue(ERROR);
        _setError.exitProgram();
    }
}

std::unique_ptr<IDisplayModule> DlLib::getLib()
{
    _lib = (std::unique_ptr<IDisplayModule> (*)(void))dlsym(_openLib, "gEpitechArcadeGetDisplayModuleHandle");

    _lib()->update();
    return (_lib());
}

void DlLib::closeLib()
{
    dlclose(_openLib);
}

void DlLib::openGame(char *str)
{
    std::string error = "ERROR: couldn't open game";

    _openGame = dlopen(str, RTLD_LAZY);
    if (!_openGame) {
        _setError.setReason(error);
        _setError.displayReason();
        _setError.setReturnValue(ERROR);
        _setError.exitProgram();
    }
}

std::unique_ptr<IGameModule> DlLib::getGame()
{
    _game = (std::unique_ptr<IGameModule> (*)(void))dlsym(_openGame, "gEpitechArcadeGetGameModuleHandle");

    _game()->update();
    return (_game());
}

void DlLib::closeGame()
{
    dlclose(_openGame);
}
