/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** CppThreads
*/

#pragma once
#include <thread>

class CppThreads {
    public:
        CppThreads();
        ~CppThreads();

        int createThread(void *(*_start_routine)(void *), void *threadParam);
        int joinThreads();

    protected:
    private:
        std::thread _thread;
};
