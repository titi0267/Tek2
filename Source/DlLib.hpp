/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** DlLib
*/

#ifndef DLLIB_HPP_
#define DLLIB_HPP_

#include "Error/Error.hpp"

class DlLib {
    public:
        DlLib();
        ~DlLib();
    void open(char *str);
    void close();
    void getLib();

    protected:
        void (*_about)(void);
        void *_open;
        Error _setError;
};

#endif /* !DLLIB_HPP_ */
