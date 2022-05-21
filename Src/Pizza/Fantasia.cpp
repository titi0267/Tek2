/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Fantasia
*/

#include "Fantasia.hpp"

Fantasia::Fantasia(uint32_t pizzaId, IPizza::PizzaSize size)
{
    _id = pizzaId;
    _size = size;

    for (int i = 0; i <= (int)IPizza::Ingredients::CHIEF_LOVE; i++) {
        _ingredients.push_back(false);
    }
    _ingredients[(int)IPizza::Ingredients::DOE] = true;
    _ingredients[(int)IPizza::Ingredients::TOMATO] = true;
    _ingredients[(int)IPizza::Ingredients::EGG] = true;
    _ingredients[(int)IPizza::Ingredients::GOAT_CHEESE] = true;
    _ingredients[(int)IPizza::Ingredients::CHIEF_LOVE] = true;
    _bakedTime = 4;
}

uint32_t Fantasia::getBakedTime()
{
    return (_bakedTime);
}

uint32_t Fantasia::getPizzaId()
{
    return (_id);
}

std::deque<bool> Fantasia::getIngredients()
{
    return (_ingredients);
}

IPizza::PizzaSize Fantasia::getPizzaSize()
{
    return (_size);
}

Fantasia::~Fantasia()
{
}
