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
    if (pizza->statusCmd == true) {
        _dump = true;
        return;
    }
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

std::unique_ptr <IPizza>ThreadPull::getFirstPizza(uint32_t cookerId)
{
    std::unique_ptr<IPizza> firstPizza = std::move(_pizzaToCook[0]);
    std::string str = "Cooker is cooking pizza nbr ";
    str += std::to_string(firstPizza->getPizzaId());
    _pizzaToCook.pop_front();
    if (_dump == true)
        std::cout << str << std::endl;
    return (firstPizza);
}

bool ThreadPull::cookPizza()
{
    int pizzaNbr = _pizzaToCook.size();

    if (pizzaNbr == 0)
        return (false);
    else {
        for (int i = 0; i < pizzaNbr; i++)
            launchThread();
        for (int i = 0; i < _isRunningThread.size(); i++) {
            if (_isRunningThread[i] == ThreadStatus::RUNNING)
                _cooker[i]->joinThreads();
        }
        if (_dump == true && pizzaNbr < _cooker.size())
            std::cout << "A cooker was doing Nothing";
        _dump = false;
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
            return;
        }
    }
}