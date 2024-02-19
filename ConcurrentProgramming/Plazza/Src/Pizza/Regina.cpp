/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Regina
*/

#include "Regina.hpp"

Regina::Regina(uint32_t pizzaId, IPizza::PizzaSize size)
{
    _id = pizzaId;
    _size = size;

    for (int i = 0; i <= (int)IPizza::Ingredients::CHIEF_LOVE; i++) {
        _ingredients.push_back(false);
    }
    _ingredients[(int)IPizza::Ingredients::DOE] = true;
    _ingredients[(int)IPizza::Ingredients::TOMATO] = true;
    _ingredients[(int)IPizza::Ingredients::GRUYERE] = true;
    _ingredients[(int)IPizza::Ingredients::HAM] = true;
    _ingredients[(int)IPizza::Ingredients::MUSHROOM] = true;
    _bakedTime = 2;
}

uint32_t Regina::getBakedTime()
{
    return (_bakedTime);
}

uint32_t Regina::getPizzaId()
{
    return (_id);
}

std::deque<bool> Regina::getIngredients()
{
    return (_ingredients);
}

IPizza::PizzaSize Regina::getPizzaSize()
{
    return (_size);
}

Regina::~Regina()
{
}
