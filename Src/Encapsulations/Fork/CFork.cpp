/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** CFork
*/

#include "CFork.hpp"

CFork::CFork(uint32_t forkNbr, uint32_t cookNbr, uint32_t cookingTimeMultiplier) : parentWrite(forkNbr), childWrite(forkNbr)
{
    parentWrite.CMakeFifo();
    childWrite.CMakeFifo();
    setPid();
    if (_childPid == 0) {
        std::unique_ptr<Kitchen> kitchen = std::make_unique<Kitchen>(forkNbr, cookNbr, cookingTimeMultiplier, parentWrite, childWrite);
        kitchen->loop();
        exit(0);
    } else {
        parentWrite.COpenFifoWrite();
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
