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
        Order(uint32_t orderId);
        ~Order();
        void pushPizza(uint32_t newId);
        std::list<uint32_t> getId() const;
        uint32_t getOrderId() const;
        void setId(std::list<uint32_t> pizzasId);
    protected:
    private:
        std::list<uint32_t> _pizzasId;
        uint32_t _orderId;
};
