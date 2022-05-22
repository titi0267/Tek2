/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Kitchen
*/

#include "Kitchen.hpp"
#include "../Pizza/SendPizza.hpp"

Kitchen::Kitchen(uint32_t id, uint32_t cookNbr, uint32_t cookingTimeMultiplier, IPC::ParentToChild &parentWrite, IPC::ChildToParent &childWrite) :
_threadPull(std::make_unique<ThreadPull>(cookNbr, cookingTimeMultiplier, childWrite)), _cookingTimeMultiplier(cookingTimeMultiplier), _id(id), _parentWrite(parentWrite), _childWrite(childWrite)
{
    std::cout << "Kitchen: " << _id << " is now open" << std::endl;
    parentWrite.COpenFifoRead();
    childWrite.COpenFifoWrite();
}

void Kitchen::loop()
{
    clock_t tmp;
    _clock = clock();
    SendPizza_t *pizza;

    while(1) {
        tmp = clock();
        _threadPull->cookPizza();
        if (_threadPull->isSomeoneCooking())
            _clock = clock();
        while (_parentWrite.test_poll()) {
            pizza = _parentWrite.CReadFifo();
            if (pizza != NULL)
                _threadPull->addPizzaToCook(pizza);
        }
        if (((double)(tmp - _clock) / (double)CLOCKS_PER_SEC) > 0.4) {
            std::cout << "The kitchen: " << _id  << " is closing" << std::endl;
            break;
        }
        _threadPull->flushFinishedThread();
    }
    _parentWrite.CCloseRd();
    _childWrite.CCloseWr();
}

Kitchen::~Kitchen()
{
}
