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
#include "../Encapsulations/Mutex/CMutex.hpp"
#include "../Pizza/IPizza.hpp"
#include "ThreadPayload.hpp"

using ThreadPayloadPtr = std::unique_ptr<ThreadPayload>;
using ThreadPtr = std::unique_ptr<CThreads>;
using pizzaPtr = std::unique_ptr<IPizza>;

void *cook(void * ptr);

class ThreadPull {
    public:
        ThreadPull(uint32_t cookNbr);
        ~ThreadPull();
        void launchThread();
        void flushFinishedThread();
        bool cookPizza();
        void setThreadFinish(uint32_t index);
        //IPizza &getFirstPizza();
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
        std::deque<pizzaPtr> _pizzaToCook;
        CMutex _pickInStock;
        CMutex _pickPizza;
};
