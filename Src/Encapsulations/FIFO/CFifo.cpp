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

SendPizza_t *CFifo::CReadFifo()
{
    SendPizza_t *pizzaInfo;

    _in.read(reinterpret_cast<char *>(&pizzaInfo), sizeof(SendPizza_t));
    return (pizzaInfo);
}

std::ofstream operator<<(std::ofstream &out, SendPizza_t *pizzaInfo)
{
    out.write(reinterpret_cast<char *>(&pizzaInfo), sizeof(SendPizza_t));
}

void CFifo::CWriteFifo(SendPizza_t *pizzaInfo)
{
    //std::cout << pizzaInfo;
    _out << pizzaInfo;
}

void CFifo::CCloseIn()
{
    _in.close();
}

void CFifo::CCloseOut()
{
    _out.close();
}
