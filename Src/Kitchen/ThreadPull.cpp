/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** ThreadPull
*/

#include "ThreadPull.hpp"

ThreadPull::ThreadPull(uint32_t cookNbr)
{
    for (int i = 0; i < cookNbr; i++) {
        _cooker.push_back(CThreads());
        _isRunningThread.push_back(ThreadStatus::FREE);
        _payloads.push_back(ThreadPayload(this, 12));
    }
    _test = 12;
}

ThreadPull::~ThreadPull()
{
}

void *cook(void * ptr)
{
    ThreadPayload *pull = (ThreadPayload *)ptr;
    std::cout << "Je suis " << pull->getId() << std::endl;
    pull->getThreadPull()->setThreadFinish(pull->getId());
    return (NULL);
}

void ThreadPull::setThreadFinish(uint32_t index)
{
    _isRunningThread[index] = ThreadStatus::FINISH;
}

void ThreadPull::flushFinishedThread()
{
    for (int i = 0; i < _isRunningThread.size(); i++) {
        if (_isRunningThread[i] == ThreadStatus::FINISH) {
            _cooker[i] = CThreads();
            _isRunningThread[i] = ThreadStatus::FREE;
        }
    }
}

void ThreadPull::launchThread()
{
    for (int i = 0; i < _isRunningThread.size(); i++) {
        if (_isRunningThread[i] == ThreadStatus::FREE) {
            _isRunningThread[i] = ThreadStatus::RUNNING;
            _cooker[i].createThread(cook, (void *)&_payloads[i]);
            _cooker[i].joinThreads();
            return;
        }
    }
}