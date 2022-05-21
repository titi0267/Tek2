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

#include "../Encapsulations/Mutex/CMutex.hpp"
#include "../Pizza/IPizza.hpp"
#include "./ThreadPull.hpp"
#include "../Encapsulations/FIFO/CFifo.hpp"

using pizzaPtr = std::unique_ptr<IPizza>;

class Kitchen {
    public:
        Kitchen(uint32_t id, uint32_t _cookNbr, uint32_t _cookingTimeMultiplier, CFifo &fifo);
        ~Kitchen();

        void loop();
        void addPizza(std::unique_ptr<IPizza> &);

    protected:
    private:
        uint32_t _id;
        ThreadPull _threadPull;
        std::deque<pizzaPtr> _pizzaToCook;
        uint32_t _cookingTimeMultiplier;
        CMutex _pickInStock;
        clock_t _clock;
        CFifo &_fifo;
};
