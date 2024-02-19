/*
** EPITECH PROJECT, 2022
** plaza
** File description:
** CMutex
*/

#pragma once

#include <pthread.h>

class CMutex {
    public:
        CMutex();
        ~CMutex();
        void lock();
        void unlock();
        int trylock();

    protected:
    private:
        pthread_mutex_t _mutex;
};
