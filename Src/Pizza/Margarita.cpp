/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Margarita
*/

#include "Margarita.hpp"

Margarita::Margarita(uint32_t pizzaId, IPizza::PizzaSize size)
{
    _id = pizzaId;
    _size = size;

    for (int i = 0; i <= (int)IPizza::Ingredients::CHIEF_LOVE; i++) {
        _ingredients.push_back(false);
    }
    _ingredients[(int)IPizza::Ingredients::DOE] = true;
    _ingredients[(int)IPizza::Ingredients::TOMATO] = true;
    _ingredients[(int)IPizza::Ingredients::GRUYERE] = true;
    _bakedTime = 1;
}

uint32_t Margarita::getBakedTime()
{
    return (_bakedTime);
}

uint32_t Margarita::getPizzaId()
{
    return (_id);
}

std::deque<bool> Margarita::getIngredients()
{
    return (_ingredients);
}

IPizza::PizzaSize Margarita::getPizzaSize()
{
    return (_size);
}

Margarita::~Margarita()
{
}
