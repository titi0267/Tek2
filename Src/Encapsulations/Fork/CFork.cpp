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

int CFork::CMakeFifo()
{
    return (mkfifo("/tmp/myfifo", 0666));
}

void CFork::COpenFifoRead()
{
    _in = std::ifstream("/tmp/myfifo", std::ios::in);
}

void CFork::COpenFifoWrite()
{
    _out = std::ofstream("/tmp/myfifo");
}

std::string CFork::CReadFifo()
{
    std::string messageRead;

    messageRead.assign((std::istreambuf_iterator<char>(_in)), (std::istreambuf_iterator<char>()));
    return (messageRead);
}

void CFork::CWriteFifo(std::string messageWrite)
{
    _out << messageWrite;
}
