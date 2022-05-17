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

#include "../Encapsulations/Mutex/CMutex.hpp"
#include "../Pizza/IPizza.hpp"
#include "./ThreadPull.hpp"

using pizzaPtr = std::unique_ptr<IPizza>;

class Kitchen {
    public:
        Kitchen(uint32_t _cookNbr, uint32_t _cookingTimeMultiplier);
        ~Kitchen();

        void addPizza(std::unique_ptr<IPizza> &);

    protected:
    private:
        ThreadPull _threadPull;
        std::deque<pizzaPtr> _pizzaToCook;
        uint32_t _cookingTimeMultiplier;
        CMutex _pickInStock;
};
