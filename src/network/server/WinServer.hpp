/*
** EPITECH PROJECT, 2022
** windows-linux-socket
** File description:
** Server
*/

#pragma once

#ifdef _WIN32

#include <memory>
#include <unordered_map>
#include "network/IServer.hpp"
#include "network/ISocket.hpp"
#include "../sockets/SocketInclude.hpp"

namespace network {
    class WinServer : public IServer {
        std::unique_ptr<ISocket> _socket;
        std::unordered_map<ConnId,uint64_t> _clients;

        std::string _ip;
        unsigned short _port;

        fd_set _readSet;
        fd_set _writeSet;

        public:
        WinServer(const std::string &ip = "", const std::string &port = "", const int maxClient = 4);
        ~WinServer() = default;

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
