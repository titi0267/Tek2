/*
** EPITECH PROJECT, 2022
** windows-linux-socket
** File description:
** WinClient
*/

#pragma once

#include "network/IClient.hpp"
#include "../sockets/SocketInclude.hpp"
#include "../sockets/ISocket.hpp"
#include <string>
#include <memory>

#ifdef _WIN32

namespace network {
    class WinClient : public IClient {
        std::unique_ptr<ISocket> _socket;
        fd_set _readSet;
        fd_set _writeSet;

        public:
        WinClient(const std::string &ip, const std::string &portString);
        ~WinClient() = default;

        void updateRWStates();

        bool canRead();
        bool canWrite();

        int read(void *buf, std::size_t size);
        void write(void *data, std::size_t size);
    };
}

#endif
