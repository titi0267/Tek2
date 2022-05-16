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
#include <sys/shm.h>
#include <sys/ipc.h>

class CFork {
    public:
        CFork();
        ~CFork();
        void CToken();
        void CGetShmId();
        void CAttachShm();
        void CShmAssemble();
        pid_t getPid() const;
        void setPid();

    protected:
    private:
        pid_t _childPid;
        key_t _token;
        int _shMId;
        char *_message;
};
