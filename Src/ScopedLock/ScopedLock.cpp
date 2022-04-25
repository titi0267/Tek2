/*
** EPITECH PROJECT, 2022
** plaza
** File description:
** ScopedLock
*/

#include "ScopedLock.hpp"

ScopedLock::ScopedLock(IMutex &mutex)
    : _mutex(mutex)
{
    _mutex.lock();
}

ScopedLock::~ScopedLock()
{
    _mutex.unlock();
}
