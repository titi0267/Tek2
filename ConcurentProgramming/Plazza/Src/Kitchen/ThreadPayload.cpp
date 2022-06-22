/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** ThreadPayload
*/

#include "ThreadPayload.hpp"

ThreadPayload::ThreadPayload(ThreadPull *pull, uint32_t id)
{
    _pull = pull;
    _id = id;
}

ThreadPayload::~ThreadPayload()
{
}

uint32_t ThreadPayload::getId()
{
    return _id;
}

ThreadPull *ThreadPayload::getThreadPull()
{
    return _pull;
}