/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Kitchen
*/

#pragma once

#include <deque>
#include <iostream>
#include <memory>
#include <time.h>

#include "./ThreadPull.hpp"
#include "../Encapsulations/FIFO/CFifo.hpp"

class Kitchen {
    public:
        Kitchen(uint32_t id, uint32_t _cookNbr, uint32_t _cookingTimeMultiplier, IPC::ParentToChild &parentWrite);
        ~Kitchen();

        void loop();

    protected:
    private:
        uint32_t _id;
        std::unique_ptr<ThreadPull> _threadPull;
        uint32_t _cookingTimeMultiplier;
        clock_t _clock;
        IPC::ParentToChild &_parentWrite;
};
