/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** CFifo
*/

#include "CFifo.hpp"

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
    _in = std::ifstream(_str, std::ios::in);
}

void CFifo::COpenFifoWrite()
{
    _out = std::ofstream(_str);
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
