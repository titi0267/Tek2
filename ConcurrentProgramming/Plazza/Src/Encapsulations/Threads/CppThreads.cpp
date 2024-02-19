/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** CppThreads
*/

#include "CppThreads.hpp"

CppThreads::CppThreads()
{
}

CppThreads::~CppThreads()
{
}

int CppThreads::createThread(void *(*start_routine)(void *), void *threadParam)
{
    _thread = std::thread(start_routine, threadParam);
}
