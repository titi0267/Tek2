/*
** EPITECH PROJECT, 2022
** plaza
** File description:
** ScopedLock
*/

#pragma once
#include "../IMutex.hpp"

class ScopedLock {
    public:
        ScopedLock(IMutex &mutex);
        ~ScopedLock();

    protected:
    private:
        IMutex &_mutex;
};
