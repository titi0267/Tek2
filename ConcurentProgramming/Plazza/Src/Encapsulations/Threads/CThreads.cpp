/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** CThreads
*/

#include "CThreads.hpp"
#include <iostream>

CThreads::CThreads()
{
}

CThreads::~CThreads()
{
}

int CThreads::createThread(void *(*_start_routine)(void *), void *threadParam)
{
    return (pthread_create(&_thread, NULL, _start_routine, threadParam));
}

int CThreads::joinThreads()
{
    return (pthread_join(_thread, NULL));
}