/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** ThreadPull
*/

#include "ThreadPull.hpp"
#include "ThreadPayload.hpp"
#include <tuple>

ThreadPull::ThreadPull(uint32_t cookNbr)
{
    for (int i = 0; i < cookNbr; i++) {
        _cooker.push_back(CThreads());
        _isRunningThread.push_back(ThreadStatus::FREE);
    }
    _test = 12;
}

ThreadPull::~ThreadPull()
{
}

void *cook(void * ptr)
{
    ThreadPayload *pull = (ThreadPayload *)ptr;
    pull->getThreadPull()->setThreadFinish(pull->getId());
    return (NULL);
}

void ThreadPull::setThreadFinish(uint32_t index)
{
    _isRunningThread[index] = ThreadStatus::FINISH;
}

void ThreadPull::launchThread()
{
    for (int i = 0; i < _isRunningThread.size(); i++) {
        if (_isRunningThread[i] == ThreadStatus::FREE) {
            ThreadPayload tmp(this, i);
            _isRunningThread[i] = ThreadStatus::RUNNING;
            _cooker[i].createThread(cook, (void *)&tmp);
            _cooker[i].joinThreads();
            return;
        }
    }
}