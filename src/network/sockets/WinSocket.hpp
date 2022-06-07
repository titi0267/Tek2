/*
** EPITECH PROJECT, 2022
** windows-linux-socket
** File description:
** WinSocket
*/

#pragma once

#include "ISocket.hpp"

#ifdef _WIN32

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
