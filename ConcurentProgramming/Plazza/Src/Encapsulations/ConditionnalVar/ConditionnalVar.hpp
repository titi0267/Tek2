/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** ConditionnalVar
*/

#pragma once
#include <pthread.h>
#include "../Mutex/CMutex.hpp"

class ConditionnalVar {
    public:
        ConditionnalVar();
        ~ConditionnalVar();
        void condWait();

    protected:
    private:
        pthread_cond_t _cv;
        pthread_mutex_t _mutex;
};
