/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** CFifo
*/

#include "CFifo.hpp"
#include <unistd.h>

CFifo::CFifo(int Id)
{
    sprintf(_str, "/tmp/myfifo%d", Id);
}

CFifo::~CFifo()
{
}

void CFifo::CMakeFifo()
{
    mkfifo(_str, 0666);
}

void CFifo::COpenFifoRead()
{
    _fdRd = open(_str, O_RDONLY);//std::ifstream("/tmp/myfifo", std::ios::in);
}

void CFifo::COpenFifoWrite()
{
    _fdWr = open(_str, O_WRONLY);//std::ofstream("/tmp/myfifo");
}

SendPizza_t *CFifo::CReadFifo()
{
    //std::cout << "Read under this" << std::endl;
    read(_fdRd, &_messageRead, sizeof(SendPizza_t));
    std::cout << "Read is fine : " << std::endl;//<< _messageRead->doe << "$"<< std::endl;
    //std::cout << "fd = " << rd << " | $" << _messageRead[0] << "$" << std::endl;
    return (&_messageRead);
}

void CFifo::CCloseRd()
{
    close(_fdRd);
}

void CFifo::CCloseWr()
{
    close(_fdWr);
}


void CFifo::CWriteFifo(SendPizza_t pizza)
{
    write(_fdWr, &pizza, sizeof(SendPizza_t));
}
