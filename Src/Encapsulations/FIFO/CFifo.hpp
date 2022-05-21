/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** CFifo
*/

#pragma once

#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include "../../Pizza/SendPizza.hpp"

class CFifo {
    public:
        CFifo(int Id);
        ~CFifo();
        CFifo(const CFifo &) = delete;
        void CMakeFifo();
        void COpenFifoRead();
        void COpenFifoWrite();
        SendPizza_t *CReadFifo();
        void CCloseIn();
        void CCloseOut();
        void CWriteFifo(SendPizza_t *pizzaInfo);

    protected:
    private:
        std::string messageRead;
        std::ifstream _in;
        std::ofstream _out;
        char _str[20];
};
