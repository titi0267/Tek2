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
        int createThread(int threadNbr, void *(*_start_routine)(void *));
        int joinThreads(int threadNbr);
        //std::deque<pthread_t> getThread();

    protected:
    private:
        std::vector<pthread_t> _thread;
};
