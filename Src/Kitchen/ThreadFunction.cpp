/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** ThreadFunction
*/

#include "ThreadPull.hpp"
#include "../Encapsulations/FIFO/CFifo.hpp"
#include <chrono>
#include <thread>

void *cook(void * ptr)
{
    ThreadPayload *pull = (ThreadPayload *)ptr;
    pull->getThreadPull()->lockPizzaMutex();
    std::unique_ptr<IPizza> pizza = std::move(pull->getThreadPull()->getFirstPizza(pull->getId()));
    pull->getThreadPull()->delockPizzaMutex();
    std::cout << "Je suis " << pull->getId() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(pizza->getBakedTime() *
    pull->getThreadPull()->getCookTime()));
    std::cout << "J'ai fini " << pizza->getPizzaId() << std::endl;
    pull->getThreadPull()->sendFinishPizza(pizza->getPizzaId());
    pull->getThreadPull()->setThreadFinish(pull->getId());
    return (NULL);
}