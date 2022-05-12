/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Reception
*/

#pragma once
#include <deque>
#include <memory>

#include "../Utils/Utils.hpp"
#include "../Pizza/IPizza.hpp"

using pizzaPtr = std::unique_ptr<IPizza>;

class Reception {
    public:
        Reception(int ac, char **av);
        ~Reception();
        void loop();

    protected:
    private:
        int _cookingTime;
        int _cooksPerKitchen;
        int _timeToReplace;
        Utils _tools;
        std::deque<pizzaPtr> pizzaQueue;
};
