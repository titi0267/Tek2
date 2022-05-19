/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

Kitchen::Kitchen(uint32_t cookNbr, uint32_t cookingTimeMultiplier) : _threadPull(cookNbr), _cookingTimeMultiplier(cookingTimeMultiplier)
{
    _threadPull.launchThread();
}

void Kitchen::addPizza(std::unique_ptr<IPizza> &pizza)
{
    _pizzaToCook.push_back(std::move(pizza));
}

Kitchen::~Kitchen()
{
}
