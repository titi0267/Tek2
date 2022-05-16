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

    _ingredients.push_back("doe");
    _ingredients.push_back("tomato");
    _ingredients.push_back("gruyere");
    _ingredients.push_back("ham");
    _ingredients.push_back("mushrooms");
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

std::deque<std::string> Regina::getIngredients()
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
