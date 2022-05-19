/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** ThreadPull
*/

#pragma once
#include <deque>
#include <iostream>
#include "../Encapsulations/Threads/CThreads.hpp"
#include "ThreadPayload.hpp"

class ThreadPull {
    public:
        ThreadPull(uint32_t cookNbr);
        ~ThreadPull();
        void launchThread();
        void flushFinishedThread();
        void setThreadFinish(uint32_t index);
        int _test;

        enum class ThreadStatus {
            FREE,
            RUNNING,
            FINISH
        };

    protected:
    private:
        std::deque<ThreadPayload> _payloads;
        std::deque<CThreads> _cooker;
        std::deque<ThreadStatus> _isRunningThread;
};
