/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Reception
*/

#pragma once
#include <deque>
#include <memory>
#include <list>

#include "../Utils/Utils.hpp"
#include "../Pizza/IPizza.hpp"
#include "../Pizza/Margarita.hpp"
#include "Order.hpp"

using pizzaPtr = std::unique_ptr<IPizza>;

class Reception {
    public:
        Reception(int ac, char **av);
        ~Reception();
        void createOrder();
        void loop();

    protected:
    private:
        int _cookingTime;
        int _cooksPerKitchen;
        int _timeToReplace;
        Utils _tools;
        std::deque<pizzaPtr> _pizzaQueue;
        std::list<Order> _orderList;
};
