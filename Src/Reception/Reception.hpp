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
#include "../Encapsulations/Threads/CThreads.hpp"
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
        void dropPizzaId(uint32_t pizzaId);
        void dropOrder();
        void setOrderId(uint32_t orderId);
        void createKitchen();
        bool checkOrder(std::string buff, uint32_t orderId);
        void sendOrder();
        std::deque<std::unique_ptr<CFork>> &getForkList();
        void createPizza(std::string pizza, std::string size, std::string number, Order &order);

    protected:
    private:
        int _cookingTime;
        int _cooksPerKitchen;
        int _timeToReplace;
        Utils _tools;
        uint32_t _orderId;
        std::deque<std::unique_ptr<CFork>> _forkList;
        std::deque<pizzaPtr> _pizzaQueue;
        //std::deque<std::unique_ptr<CFifo>> _fifoList;
        std::list<Order> _orderList;
        std::list<uint32_t> _pizzasId;
        std::deque<CThreads> _recptionThread;
};
