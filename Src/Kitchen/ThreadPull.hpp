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
#include "../Encapsulations/FIFO/CFifo.hpp"
#include "../Pizza/IPizza.hpp"
#include "../Pizza/Margarita.hpp"
#include "../Pizza/Regina.hpp"
#include "../Pizza/Fantasia.hpp"
#include "../Pizza/Americana.hpp"
#include "../Pizza/SendPizza.hpp"
#include "ThreadPayload.hpp"

using ThreadPayloadPtr = std::unique_ptr<ThreadPayload>;
using ThreadPtr = std::unique_ptr<CThreads>;
using pizzaPtr = std::unique_ptr<IPizza>;

void *cook(void * ptr);

class ThreadPull {
    public:
        ThreadPull(uint32_t cookNbr, uint32_t cookTimeMultiplier, IPC::ChildToParent &fifo);
        ~ThreadPull();
        void launchThread();
        void flushFinishedThread();
        bool cookPizza();
        void setThreadFinish(uint32_t index);
        uint32_t getCookTime();
        void addPizzaToCook(SendPizza_t *pizza);
        void sendFinishPizza(uint32_t id);
        bool isSomeoneCooking();
        std::unique_ptr <IPizza>getFirstPizza(uint32_t cookerId);
        void lockPizzaMutex();
        void delockPizzaMutex();

        enum class ThreadStatus {
            FREE,
            RUNNING,
            FINISH
        };

    protected:
    private:
        bool _dump;
        std::deque<ThreadPayloadPtr> _payloads;
        std::deque<ThreadPtr> _cooker;
        std::deque<ThreadStatus> _isRunningThread;
        std::deque<pizzaPtr> _pizzaToCook;
        CMutex _pickInStock;
        CMutex _pickPizza;
        IPC::ChildToParent &_childToParent;
        uint32_t _cookTimeMultiplier;
};
