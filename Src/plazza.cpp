/*
** EPITECH PROJECT, 2022
** plaza
** File description:
** plaza
*/

#include <threads.h>
#include <iostream>
#include "Encapsulations/Mutex/CMutex.hpp"

CMutex mutex;

void *incrementCounter(void *counter)
{
    mutex.lock();
    int *value = (int *)counter;
    *value += 12;
    mutex.unlock();
    return ((void *)value);
}

int main()
{
    int counter = 0;
    pthread_t first;
    pthread_t second;
    pthread_t third;

    pthread_create(&first, NULL, incrementCounter, &counter);
    pthread_create(&second, NULL, incrementCounter, &counter);
    pthread_create(&third, NULL, incrementCounter, &counter);

    pthread_join(first, NULL);
    pthread_join(second, NULL);
    pthread_join(third, NULL);

    std::cout << counter << std::endl;
    return (0);
}