/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Cfifo
*/

#include "CFifo.hpp"
#include <unistd.h>

IPC::ParentToChild::ParentToChild(int Id)
{
    sprintf(_PToC, "/tmp/myfifo%d", Id);
}

IPC::ParentToChild::~ParentToChild()
{
}

void IPC::ParentToChild::CMakeFifo()
{
    mkfifo(_PToC, 0666);
}

void IPC::ParentToChild::COpenFifoRead()
{
    _fdRd = open(_PToC, O_RDONLY);
}

void IPC::ParentToChild::COpenFifoWrite()
{
    _fdWr = open(_PToC, O_WRONLY);
}

SendPizza_t *IPC::ParentToChild::CReadFifo()
{
    int ret = read(_fdRd, &_messageRead, sizeof(SendPizza_t));
    if (ret == 0)
        return (NULL);
    return (&_messageRead);
}

void IPC::ParentToChild::CCloseRd()
{
    close(_fdRd);
}

void IPC::ParentToChild::CCloseWr()
{
    close(_fdWr);
}

bool IPC::ParentToChild::test_poll()
{
    struct pollfd fd = {.fd = _fdRd, .events = POLLIN, .revents = 0};
    return (poll(&fd, 1, 1) == 1);
}

void IPC::ParentToChild::CWriteFifo(SendPizza_t *pizza)
{
    write(_fdWr, pizza, sizeof(SendPizza_t));
}

/***********************************************************************/

IPC::ChildToParent::ChildToParent(int Id)
{
    sprintf(_CToP, "/tmp/myfifoX%d", Id);
}

IPC::ChildToParent::~ChildToParent()
{
}

void IPC::ChildToParent::CMakeFifo()
{
    mkfifo(_CToP, 0666);
}

void IPC::ChildToParent::COpenFifoRead()
{
    _fdRd = open(_CToP, O_RDONLY | O_NONBLOCK);
}

void IPC::ChildToParent::COpenFifoWrite()
{
    _fdWr = open(_CToP, O_WRONLY);
}

uint32_t IPC::ChildToParent::CReadFifo()
{
    int ret = read(_fdRd, &_messageRead, sizeof(uint32_t));
    if (ret == 0)
        return (0);
    return (_messageRead);
}

void IPC::ChildToParent::CCloseRd()
{
    close(_fdRd);
}

void IPC::ChildToParent::CCloseWr()
{
    close(_fdWr);
}

bool IPC::ChildToParent::test_poll()
{
    struct pollfd fd = {.fd = _fdRd, .events = POLLIN, .revents = 0};
    return (poll(&fd, 1, 1) == 1);
}

void IPC::ChildToParent::CWriteFifo(uint32_t Id)
{
    write(_fdWr, &Id, sizeof(uint32_t));
}

