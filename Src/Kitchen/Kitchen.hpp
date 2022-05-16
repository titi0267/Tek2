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

#include "../Encapsulations/Threads/CThreads.hpp"
#include "../Encapsulations/Mutex/CMutex.hpp"
#include "../Pizza/IPizza.hpp"

using pizzaPtr = std::unique_ptr<IPizza>;

class Kitchen {
    public:
        Kitchen(uint32_t _cookNbr, uint32_t _cookingTimeMultiplier);
        ~Kitchen();

        void addPizza(std::unique_ptr<IPizza> &);

    protected:
    private:
        std::deque<CThreads> _cooker;
        std::deque<pizzaPtr> _pizzaToCook;
        uint32_t _cookingTimeMultiplier;
        CMutex _pickInStock;
};
