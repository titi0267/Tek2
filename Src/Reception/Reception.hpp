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
#include <climits>

#include "../Utils/Utils.hpp"
#include "../Pizza/IPizza.hpp"
#include "../Pizza/Margarita.hpp"
#include "../Pizza/Regina.hpp"
#include "../Pizza/Fantasia.hpp"
#include "../Pizza/Americana.hpp"
#include "../Encapsulations/Fork/CFork.hpp"
#include "../Encapsulations/FIFO/CFifo.hpp"
#include "../Kitchen/Kitchen.hpp"
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
        void createKitchen(uint32_t kitchenId);
        bool checkOrder(std::string buff, uint32_t orderId);
        void sendOrder();
        void createPizza(std::string pizza, std::string size, std::string number, Order &order);

    protected:
    private:
        int _cookingTime;
        int _cooksPerKitchen;
        int _timeToReplace;
        Utils _tools;
        uint32_t _orderId;
        std::deque<pizzaPtr> _pizzaQueue;
        std::deque<std::unique_ptr<Kitchen>> _runningKitchens;
        std::deque<CFifo> _fifoList;
        std::list<Order> _orderList;
        std::list<uint32_t> _pizzasId;
};
