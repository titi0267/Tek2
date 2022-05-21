/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** ThreadPull
*/

#pragma once
#include <deque>
#include <iostream>
#include <memory>

#include "../Encapsulations/Threads/CThreads.hpp"
#include "ThreadPayload.hpp"

using ThreadPayloadPtr = std::unique_ptr<ThreadPayload>;
using ThreadPtr = std::unique_ptr<CThreads>;

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
        std::deque<ThreadPayloadPtr> _payloads;
        std::deque<ThreadPtr> _cooker;
        std::deque<ThreadStatus> _isRunningThread;
};
