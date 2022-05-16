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

    _ingredients.push_back("doe");
    _ingredients.push_back("tomato");
    _ingredients.push_back("gruyere");
    _ingredients.push_back("steak");
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

std::deque<std::string> Americana::getIngredients()
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
