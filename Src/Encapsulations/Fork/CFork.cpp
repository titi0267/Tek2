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

void CFork::CToken()
{
    if ((_token = ftok("/tmp", 'A')) == -1)
        std::cout << "Key gen failed" << std::endl;
}

void CFork::CGetShmId()
{
    if ((_shMId = shmget(_token, 1024, 0666|IPC_CREAT)) == -1)
        std::cout << "Generate memory segment id failed" << std::endl;
}

void CFork::CAttachShm()
{
    if ((_message = (char *)shmat(_shMId, NULL, 0)) == (void *)-1)
        std::cout << "Attach shared memory with shared memory id failed" << std::endl;
}

void CFork::CShmAssemble()
{
    CToken();
    CGetShmId();
    CAttachShm();
}
