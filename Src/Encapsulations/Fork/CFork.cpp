/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** CFork
*/

#include "CFork.hpp"

CFork::CFork(uint32_t forkNbr, uint32_t cookNbr, uint32_t cookingTimeMultiplier) : cfifo(forkNbr)
{
    setPid();
    if (_childPid == 0) {
        cfifo.CMakeFifo();
        cfifo.COpenFifoRead();
        std::cout << "Enfant: " << cfifo.CReadFifo() << std::endl;
        std::unique_ptr<Kitchen> kitchen = std::make_unique<Kitchen>(forkNbr, cookNbr, cookingTimeMultiplier, cfifo);
        kitchen->loop();
        cfifo.CCloseIn();
        cfifo.COpenFifoWrite();
        cfifo.CWriteFifo("String from child");
        cfifo.CCloseOut();
        exit(0);
    } else {
        cfifo.COpenFifoWrite();
        cfifo.CWriteFifo("String from parent");
        cfifo.CCloseOut();
        cfifo.COpenFifoRead();
        std::cout << "Parent: " << cfifo.CReadFifo() << std::endl;
        cfifo.CCloseIn();
    }
}

CFork::~CFork()
{
}

void CFork::CKillPid()
{
    kill(getPid(), SIGKILL);
}

void CFork::setPid()
{
    if ((_childPid = fork()) == -1)
        std::cout << "Child pid error" << std::endl;
}

pid_t CFork::getPid() const
{
    return (_childPid);
}
