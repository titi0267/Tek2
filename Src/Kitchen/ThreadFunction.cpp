/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** ThreadFunction
*/

#include "ThreadPull.hpp"

void *cook(void * ptr)
{
    ThreadPayload *pull = (ThreadPayload *)ptr;
    std::cout << "Je suis " << pull->getId() << std::endl;
    pull->getThreadPull()->setThreadFinish(pull->getId());
    return (NULL);
}