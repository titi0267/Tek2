/*
** EPITECH PROJECT, 2022
** windows-linux-socket
** File description:
** LinuxSocket
*/

#pragma once

#include "ISocket.hpp"

#ifdef __linux__

namespace network {
    class LinuxSocket : public ISocket {
        public:
            LinuxSocket();
            ~LinuxSocket();
            unsigned int getSocket() const;
        protected:
            unsigned int _socket;
        private:
    };
}

#endif