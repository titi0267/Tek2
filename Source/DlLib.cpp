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
    ;
}

DlLib::~DlLib()
{
}

void DlLib::openLib(const char *str)
{
    _openLib = dlopen(str, RTLD_LAZY);
}

void DlLib::tryDownloadLib()
{
    _lib = (std::unique_ptr<IDisplayModule> (*)(void))dlsym(_openLib, "gEpitechArcadeGetDisplayModuleHandle");
}

std::unique_ptr<IDisplayModule> DlLib::getLib()
{
    return (_lib());
}

void DlLib::closeLib()
{
    dlclose(_openLib);
}

void DlLib::openGame(const char *str)
{
    _openGame = dlopen(str, RTLD_LAZY);
}

void DlLib::tryDownloadGame()
{
    _game = (std::unique_ptr<IGameModule> (*)(void))dlsym(_openGame, "gEpitechArcadeGetGameModuleHandle");
}

std::unique_ptr<IGameModule> DlLib::getGame()
{
    return (_game());
}

void DlLib::closeGame()
{
    dlclose(_openGame);
}
