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

class ThreadPull {
    public:
        ThreadPull(uint32_t cookNbr);
        ~ThreadPull();
        void launchThread();
        void setThreadFinish(uint32_t index);
        int _test;

        enum class ThreadStatus {
            FREE,
            RUNNING,
            FINISH
        };

    protected:
    private:
        std::deque<CThreads> _cooker;
        std::deque<ThreadStatus> _isRunningThread;
};
