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
    _threadPull->launchThread();
}

void Kitchen::addPizza(std::unique_ptr<IPizza> &pizza)
{
    _pizzaToCook.push_back(std::move(pizza));
}

void Kitchen::loop()
{
    clock_t tmp;
    _clock = clock();


    while(1) {
        tmp = clock();
        _fifo.COpenFifoRead();
        _fifo.CReadFifo();
        _fifo.CCloseIn();
/*        _fifo.COpenFifoWrite(); //ici -> write pour passer au parent
        _fifo.CWriteFifo("");
        _fifo.CCloseOut();*/
        if (((tmp - _clock) / CLOCKS_PER_SEC) > 3) {
            std::cout << "The kitchen: " << _id  << " is closing" << std::endl;
            break;
        }
    }
}

Kitchen::~Kitchen()
{
}
