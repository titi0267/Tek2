/*
** EPITECH PROJECT, 2022
** plaza
** File description:
** CMutex
*/

#pragma once

#include "../IMutex.hpp"
#include <pthread.h>


class CMutex: public IMutex {
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
