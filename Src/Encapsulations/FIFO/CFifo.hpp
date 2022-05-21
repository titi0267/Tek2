/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** CFifo
*/

#pragma once

#include <sys/types.h>
#include <sys/stat.h>
#include <poll.h>
#include <iostream>
#include <fstream>
#include <fcntl.h>
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
        void CCloseRd();
        void CCloseWr();
        void CWriteFifo(SendPizza_t *pizzaInfo);

    protected:
    private:
        SendPizza_t *_messageRead;
        int _fdRd;
        int _fdWr;
        char _str[20];
};
