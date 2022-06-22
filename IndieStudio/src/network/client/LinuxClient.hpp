/*
** EPITECH PROJECT, 2022
** windows-linux-socket
** File description:
** LinuxClient
*/

#pragma once

#ifdef __linux__

#include "network/IClient.hpp"
#include "network/ISocket.hpp"
#include <string>
#include <memory>

namespace network {
    class LinuxClient : public IClient {
        std::unique_ptr<ISocket> _socket;
        fd_set _readSet;
        fd_set _writeSet;
        bool _connected;

        public:
        LinuxClient();
        ~LinuxClient() = default;

        void connectTo(const std::string &ip, const std::string &portString);
        void disconnect();

        void updateRWStates();

        bool canRead();
        bool canWrite();

        int read(void *buf, std::size_t size);
        void write(void *data, std::size_t size);

        bool isConnected() { return _connected; };
    };
}

#endif
