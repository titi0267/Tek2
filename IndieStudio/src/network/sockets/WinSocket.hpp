/*
** EPITECH PROJECT, 2022
** windows-linux-socket
** File description:
** WinSocket
*/

#pragma once

#ifdef _WIN32

#include "network/ISocket.hpp"

namespace network {
    class WinSocket : public ISocket {
        public:
            WinSocket();
            ~WinSocket();
            unsigned int getSocket() const;
        protected:
            unsigned int _socket;
        private:
    };
}

#endif
