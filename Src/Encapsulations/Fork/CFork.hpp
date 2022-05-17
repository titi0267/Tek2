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

class CFork {
    public:
        CFork();
        ~CFork();
        int CMakeFifo();
        void COpenFifoRead();
        void COpenFifoWrite();
        std::string CReadFifo();
        void CWriteFifo(std::string messageWrite);
        void CKillPid();
        pid_t getPid() const;
        void setPid();

    protected:
    private:
        pid_t _childPid;
        std::string messageRead;
        std::ifstream _in;
        std::ofstream _out;
};
