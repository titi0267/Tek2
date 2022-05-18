/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** CFork
*/

#include "CFork.hpp"

CFork::CFork()
{
    setPid();
}

CFork::~CFork()
{
}

void CFork::CCreateChild()
{
    setPid();
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
