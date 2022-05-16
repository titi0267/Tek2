/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** CFork
*/

#pragma once
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <signal.h>

class CFork {
    public:
        CFork();
        ~CFork();

    protected:
        pid_t getPid() const;
        void setPid();
    private:
        pid_t _childPid;
};
