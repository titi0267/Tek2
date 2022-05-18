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
#include <tuple>

#include "../Utils/Utils.hpp"
#include "../Pizza/IPizza.hpp"
#include "../Pizza/Margarita.hpp"
#include "../Encapsulations/Fork/CFork.hpp"
#include "../Encapsulations/FIFO/CFifo.hpp"
#include "Order.hpp"

using pizzaPtr = std::unique_ptr<IPizza>;

class Reception {
    public:
        Reception(int ac, char **av);
        ~Reception();
        void createOrder(uint32_t orderId);
        void loop();
        void dropPizzaId(uint32_t orderId);
        void dropOrder();
        void setOrderId(uint32_t orderId);
        void createKitchen();

    protected:
    private:
        int _cookingTime;
        int _cooksPerKitchen;
        int _timeToReplace;
        Utils _tools;
        uint32_t _orderId;
        std::deque<pizzaPtr> _pizzaQueue;
        std::list<Order> _orderList;
        std::list<uint32_t> _pizzasId;
        CFork cfork;
        CFifo cfifo;
};
