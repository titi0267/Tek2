/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** DlLib
*/

#include "DlLib.hpp"
#include "define.hpp"
#include <iostream>

DlLib::DlLib()
{
}

DlLib::~DlLib()
{
}

void *DlLib::openLib(const char *str)
{
    _openLib = dlopen(str, RTLD_LAZY);
    return _openLib;
}

char *DlLib::tryDownloadLib()
{
    char *error;

    _lib = (std::unique_ptr<IDisplayModule> (*)(void))dlsym(_openLib, "gEpitechArcadeGetDisplayModuleHandle");

    error = dlerror();
    return error;
}

std::unique_ptr<IDisplayModule> DlLib::getLib()
{
    return (_lib());
}

int DlLib::closeLib()
{
    return dlclose(_openLib);
}

void *DlLib::openGame(const char *str)
{
    _openGame = dlopen(str, RTLD_LAZY);
    return (_openGame);
}

char *DlLib::tryDownloadGame()
{
    char *error;
    _game = (std::unique_ptr<IGameModule> (*)(void))dlsym(_openGame, "gEpitechArcadeGetGameModuleHandle");

    error = dlerror();
    return error;
}

std::unique_ptr<IGameModule> DlLib::getGame()
{
    return (_game());
}

int DlLib::closeGame()
{
    return dlclose(_openGame);
}
