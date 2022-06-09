/*
** EPITECH PROJECT, 2022
** windows-linux-socket
** File description:
** Server
*/

#pragma once

#ifdef __linux__

#include <memory>
#include <unordered_map>
#include "network/IServer.hpp"
#include "network/ISocket.hpp"

namespace network {
    class LinuxServer : public IServer {
        std::unique_ptr<ISocket> _socket;
        std::unordered_map<ConnId, SocketFd> _clients;

        std::string _ip;
        unsigned short _port;

        fd_set _readSet;
        fd_set _writeSet;

        public:
        LinuxServer(const std::string &ip = "", const std::string &port = "", const int maxClient = 4);
        ~LinuxServer() = default;

        void updateRWStates();

        bool canAcceptConn();
        bool canRead(ConnId id);
        bool canWrite(ConnId id);

        ConnId acceptClient();
        int read(ConnId id, void *buf, std::size_t size);
        void write(ConnId id, void *data, std::size_t size);

        unsigned short getServerPort() const { return _port; };
        const std::string &getServerIp() const { return _ip; };

        void disconnectConn(ConnId conn);

        void setPortFromSocket();
        std::string findIp();
    };
}

#endif
