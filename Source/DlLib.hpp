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
        DlLib(char *libName);
        ~DlLib();
    void open(char *str);
    void close();
    std::unique_ptr<IDisplayModule> getLib();
    std::unique_ptr<IGameModule> getGame();

    protected:
        void (*_lib)(void);
        void (*_game)(void);
        void *_open;
        Error _setError;
};

#endif /* !DLLIB_HPP_ */
