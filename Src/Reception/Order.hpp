/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Order
*/

#pragma once

#include <list>
#include <iostream>

class Order {
    public:
        Order();
        ~Order();
        void pushPizza(uint32_t newId);

    protected:
    private:
        std::list<uint32_t> _pizzasId;
};
