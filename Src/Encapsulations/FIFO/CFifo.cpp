/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** CFifo
*/

#include "CFifo.hpp"

CFifo::CFifo()
{
}

CFifo::~CFifo()
{
}

void CFifo::CMakeFifo()
{
    mkfifo("/tmp/myfifo", 0666);
}

void CFifo::COpenFifoRead()
{
    _in = std::ifstream("/tmp/myfifo", std::ios::in);
}

void CFifo::COpenFifoWrite()
{
    _out = std::ofstream("/tmp/myfifo");
}

std::string CFifo::CReadFifo()
{
    std::string messageRead;

    messageRead.assign((std::istreambuf_iterator<char>(_in)), (std::istreambuf_iterator<char>()));
    return (messageRead);
}

void CFifo::CWriteFifo(std::string messageWrite)
{
    std::cout << messageWrite;
    _out << messageWrite;
}

void CFifo::CCloseIn()
{
    _in.close();
}

void CFifo::CCloseOut()
{
    _out.close();
}
