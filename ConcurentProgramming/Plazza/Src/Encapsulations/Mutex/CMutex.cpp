/*
** EPITECH PROJECT, 2022
** plaza
** File description:
** CMutex
*/

#include "CMutex.hpp"

CMutex::CMutex()
{
    pthread_mutex_init(&_mutex, NULL);
}

void CMutex::lock()
{
    pthread_mutex_lock(&_mutex);
}

void CMutex::unlock()
{
    pthread_mutex_unlock(&_mutex);
}

int CMutex::trylock()
{
    return (pthread_mutex_trylock(&_mutex));
}

CMutex::~CMutex()
{
    pthread_mutex_destroy(&_mutex);
}
