/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** DlLib
*/

#ifndef DLLIB_HPP_
#define DLLIB_HPP_

#include "Error/Error.hpp"
#include "../arcade-interface-master/IDisplayModule.hpp"
#include "../arcade-interface-master/IGameModule.hpp"

extern "C" {
    #include <dlfcn.h>
}

class DlLib {
    public:
        DlLib(char *libName, char *gameName);
        ~DlLib();
    void openGame(char *str);
    void openLib(char *str);
    void closeGame();
    void closeLib();
    std::unique_ptr<IDisplayModule> getLib();
    std::unique_ptr<IGameModule> getGame();

    protected:
        std::unique_ptr<IDisplayModule> (*_lib)(void);
        std::unique_ptr<IGameModule> (*_game)(void);
        void *_openLib;
        void *_openGame;
        Error _setError;
};

#endif /* !DLLIB_HPP_ */
