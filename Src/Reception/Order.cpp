/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Order
*/

#include "Order.hpp"

Order::Order(uint32_t orderId)
{
    _orderId = orderId;
}

Order::~Order()
{
}

void Order::pushPizza(uint32_t newId)
{
    _pizzasId.push_back(newId);
}

std::list<uint32_t> Order::getId() const
{
    return (_pizzasId);
}

uint32_t Order::getOrderId() const
{
    return (_orderId);
}

void Order::setId(std::list<uint32_t> pizzasId)
{
    _pizzasId = pizzasId;
}