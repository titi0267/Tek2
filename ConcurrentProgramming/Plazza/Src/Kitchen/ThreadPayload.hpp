/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** ThreadPayload
*/

#pragma once
#include <iostream>
#include <cstdint>

class ThreadPull;
class ThreadPayload {
    public:
        ThreadPayload(ThreadPull *pull, uint32_t id);
        uint32_t getId();
        ThreadPull *getThreadPull();
        ~ThreadPayload();

    protected:
    private:
        uint32_t _id;
        ThreadPull *_pull;
};
