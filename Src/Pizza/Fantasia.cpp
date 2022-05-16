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

    _ingredients.push_back("doe");
    _ingredients.push_back("tomato");
    _ingredients.push_back("eggplant");
    _ingredients.push_back("goat cheese");
    _ingredients.push_back("chief love");
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

std::deque<std::string> Fantasia::getIngredients()
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
