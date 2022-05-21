/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Americana
*/

#include "Americana.hpp"

Americana::Americana(uint32_t pizzaId, IPizza::PizzaSize size)
{
    _id = pizzaId;
    _size = size;

    for (int i = 0; i <= (int)IPizza::Ingredients::CHIEF_LOVE; i++) {
        _ingredients.push_back(false);
    }
    _ingredients[(int)IPizza::Ingredients::DOE] = true;
    _ingredients[(int)IPizza::Ingredients::TOMATO] = true;
    _ingredients[(int)IPizza::Ingredients::GRUYERE] = true;
    _ingredients[(int)IPizza::Ingredients::STEAK] = true;
    _bakedTime = 2;
}

uint32_t Americana::getBakedTime()
{
    return (_bakedTime);
}

uint32_t Americana::getPizzaId()
{
    return (_id);
}

std::deque<bool> Americana::getIngredients()
{
    return (_ingredients);
}

IPizza::PizzaSize Americana::getPizzaSize()
{
    return (_size);
}

Americana::~Americana()
{
}
