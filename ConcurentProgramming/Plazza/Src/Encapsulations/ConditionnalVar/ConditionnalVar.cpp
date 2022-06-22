/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** ConditionnalVar
*/

#include "ConditionnalVar.hpp"

ConditionnalVar::ConditionnalVar()
{
    pthread_cond_init(&_cv, NULL);
    pthread_mutex_init(&_mutex, NULL);
}

ConditionnalVar::~ConditionnalVar()
{
}

void ConditionnalVar::condWait()
{
    pthread_cond_wait(&_cv, &_mutex);
}
