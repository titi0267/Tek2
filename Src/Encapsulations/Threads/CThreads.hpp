/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** CThreads
*/

#pragma once
#include <pthread.h>
#include <stdlib.h>
#include <vector>

class CThreads {
    public:
        CThreads();
        ~CThreads();
        int createThread(void *(*_start_routine)(void *), void *threadParam);
        int joinThreads();

    protected:
    private:
        pthread_t _thread;
};
