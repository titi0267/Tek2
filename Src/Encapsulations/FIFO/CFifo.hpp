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

class CFifo {
    public:
        CFifo(int Id);
        ~CFifo();
        void CMakeFifo();
        void COpenFifoRead();
        void COpenFifoWrite();
        std::string CReadFifo();
        void CCloseIn();
        void CCloseOut();
        void CWriteFifo(std::string messageWrite);

    protected:
    private:
        std::string messageRead;
        std::ifstream _in;
        std::ofstream _out;
        char _str[20];
};
