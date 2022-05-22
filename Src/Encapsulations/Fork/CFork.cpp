/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** CFork
*/

#include "CFork.hpp"

CFork::CFork(uint32_t forkNbr, uint32_t cookNbr, uint32_t cookingTimeMultiplier) : parentWrite(forkNbr), childWrite(forkNbr)
{
    setPid();
    parentWrite.CMakeFifo();
    childWrite.CMakeFifo();
    if (_childPid == 0) {
        std::unique_ptr<Kitchen> kitchen = std::make_unique<Kitchen>(forkNbr, cookNbr, cookingTimeMultiplier, parentWrite, childWrite);
        kitchen->loop();
/*        cfifo.COpenFifoWrite();
        cfifo.CWriteFifo("String from child");
        cfifo.CCloseOut();*/
        exit(0);
    } else {
        childWrite.COpenFifoRead();
    }
}

CFork::~CFork()
{
    childWrite.CCloseRd();
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
