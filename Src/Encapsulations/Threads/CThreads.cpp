/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** CThreads
*/

#include "CThreads.hpp"

CThreads::CThreads()
{
}

CThreads::~CThreads()
{
}

int CThreads::createThread(int threadNbr, void *(*_start_routine)(void *))
{
    return (pthread_create(&_thread[threadNbr], NULL, _start_routine, (void *)threadNbr));
}

int CThreads::joinThreads(int threadNbr)
{
    return (pthread_join(_thread[threadNbr], NULL));
}