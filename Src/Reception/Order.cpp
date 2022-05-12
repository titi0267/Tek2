/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Order
*/

#include "Order.hpp"

Order::Order()
{
}

Order::~Order()
{
}

void Order::pushPizza(uint32_t newId)
{
    _pizzasId.push_back(newId);
}