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
    std::cout << "construct dl" << std::endl;
}

DlLib::~DlLib()
{
    std::cout << "destroy dl" << std::endl;
}

void *DlLib::openLib(const char *str)
{
    std::cout << "open " << str << std::endl;
    _openLib = dlopen(str, RTLD_LAZY);
    return _openLib;
}

char *DlLib::tryDownloadLib()
{
    char *error;

    _lib = (std::unique_ptr<IDisplayModule> (*)(void))dlsym(_openLib, "gEpitechArcadeGetDisplayModuleHandle");

    error = dlerror();
    if (error == NULL) {
        std::cout << "test lib" << std::endl;
        _lib()->startTextInput();
        std::cout << "test passe" << std::endl;
    }
    return error;
}

std::unique_ptr<IDisplayModule> DlLib::getLib()
{
    std::cout << "get lib" << std::endl;
    _lib()->startTextInput();
    std::cout << "lib work" << std::endl;
    return (_lib());
}

int DlLib::closeLib()
{
    std::cout << "close at "<< _openLib << std::endl;
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
