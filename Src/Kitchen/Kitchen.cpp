/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

Kitchen::Kitchen(uint32_t id, uint32_t cookNbr, uint32_t cookingTimeMultiplier, CFifo &fifo) :
_threadPull(std::make_unique<ThreadPull>(cookNbr)), _cookingTimeMultiplier(cookingTimeMultiplier), _id(id), _fifo(fifo)
{
    std::cout << "Kitchen: " << _id << " is now open" << std::endl;
}

void Kitchen::loop()
{
    clock_t tmp;
    _clock = clock();
    bool isPizzaToCook = false;

    while(1) {
        tmp = clock();
        isPizzaToCook = _threadPull->cookPizza();
        if (isPizzaToCook)
            _clock = clock();
        if (((tmp - _clock) / CLOCKS_PER_SEC) > 3) {
            std::cout << "The kitchen: " << _id  << " is closing" << std::endl;
            break;
        }
    }
}

Kitchen::~Kitchen()
{
}
