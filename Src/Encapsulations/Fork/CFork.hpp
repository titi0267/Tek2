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
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include "../FIFO/CFifo.hpp"
#include "../../Kitchen/Kitchen.hpp"

class CFork {
    public:
        CFork(uint32_t forkNumber,  uint32_t cookNbr, uint32_t cookingTimeMultiplier);
        ~CFork();
        void CKillPid();
        pid_t getPid() const;
        IPC::ParentToChild parentWrite;

    protected:
        void setPid();
    private:
        pid_t _childPid;
};
