/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Stock
*/

#include "Stock.hpp"

Stock::Stock()
{
    for (int i = 0; i <= (uint32_t)Stock::Ingredients::CHIEF_LOVE; i++)
        _ingredients.push_back(5);
}

Stock::~Stock()
{
}

void Stock::refillAll()
{
    for (int i = 0; i <= (uint32_t)Stock::Ingredients::CHIEF_LOVE; i++)
        _ingredients[i] += 1;
}

int Stock::takeInStock(Ingredients index)
{
    if (_ingredients[(int)index] == 0)
        return (-1);
    return (_ingredients[(int)index]--);
}