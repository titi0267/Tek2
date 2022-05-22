/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** ThreadPull
*/

#include "ThreadPull.hpp"

ThreadPull::ThreadPull(uint32_t cookNbr, uint32_t cookTimeMultiplier, IPC::ChildToParent &fifo) : _cookTimeMultiplier(cookTimeMultiplier), _childToParent(fifo)
{
    for (int i = 0; i < cookNbr; i++) {
        _cooker.push_back(std::make_unique<CThreads>());
        _isRunningThread.push_back(ThreadStatus::FREE);
        _payloads.push_back(std::make_unique<ThreadPayload>(this, i));
    }
}

ThreadPull::~ThreadPull()
{
}

void ThreadPull::addPizzaToCook(SendPizza_t *pizza)
{
    std::cout << "Je suis la taille: " << pizza->size << std::endl;
    if (pizza->chief_love == 1) {
        _pizzaToCook.push_back(std::make_unique<Fantasia>(pizza->pizzaId, (IPizza::PizzaSize)pizza->size));
        return;
    }
    if (pizza->steak == 1) {
        _pizzaToCook.push_back(std::make_unique<Americana>(pizza->pizzaId, (IPizza::PizzaSize)pizza->size));
        return;
    }
    if (pizza->ham == 1) {
        _pizzaToCook.push_back(std::make_unique<Americana>(pizza->pizzaId, (IPizza::PizzaSize)pizza->size));
        return;
    }
    _pizzaToCook.push_back(std::make_unique<Margarita>(pizza->pizzaId, (IPizza::PizzaSize)pizza->size));
}

uint32_t ThreadPull::getCookTime()
{
    return (_cookTimeMultiplier);
}

void ThreadPull::sendFinishPizza(uint32_t id)
{
    _childToParent.CWriteFifo(id);
}

std::unique_ptr <IPizza>ThreadPull::getFirstPizza()
{
    std::unique_ptr<IPizza> firstPizza = std::move(_pizzaToCook[0]);
    _pizzaToCook.pop_front();
    return (firstPizza);
}

bool ThreadPull::cookPizza()
{
    if (_pizzaToCook.size() == 0)
        return (false);
    else {
        launchThread();
        return (true);
    }
}

void ThreadPull::lockPizzaMutex()
{
    _pickPizza.lock();
}

void ThreadPull::delockPizzaMutex()
{
    _pickPizza.unlock();
}

bool ThreadPull::isSomeoneCooking()
{
    for (int i = 0; i < _isRunningThread.size(); i++) {
        if (_isRunningThread[i] != ThreadStatus::FREE)
            return (true);
    }
    return (false);
}

void ThreadPull::setThreadFinish(uint32_t index)
{
    _isRunningThread[index] = ThreadStatus::FINISH;
}

void ThreadPull::flushFinishedThread()
{
    for (int i = 0; i < _isRunningThread.size(); i++) {
        if (_isRunningThread[i] == ThreadStatus::FINISH) {
            _cooker[i] = std::make_unique<CThreads>();
            _isRunningThread[i] = ThreadStatus::FREE;
        }
    }
}

void ThreadPull::launchThread()
{
    for (int i = 0; i < _isRunningThread.size(); i++) {
        if (_isRunningThread[i] == ThreadStatus::FREE) {
            _isRunningThread[i] = ThreadStatus::RUNNING;
            _cooker[i]->createThread(cook, (void *)_payloads[i].get());
            _cooker[i]->joinThreads();
            return;
        }
    }
}