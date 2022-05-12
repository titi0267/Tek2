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

    _ingredients.push_back("doe");
    _ingredients.push_back("tomato");
    _ingredients.push_back("gruyere");
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

std::deque<std::string> Margarita::getIngredients()
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
