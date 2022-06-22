/*
** EPITECH PROJECT, 2022
** windows-linux-socket
** File description:
** LinuxSocket
*/

#pragma once

#ifdef __linux__

#include "network/ISocket.hpp"

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