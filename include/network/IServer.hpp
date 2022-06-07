/*
** EPITECH PROJECT, 2022
** windows-linux-socket
** File description:
** IServer
*/

#pragma once

#include <vector>
#include <string>

namespace network {
    using ConnId = unsigned int;
    using SocketFd = int;

    class IServer {
        public:
            virtual ~IServer() = default;

            virtual void updateRWStates() = 0;

            virtual bool canAcceptConn() = 0;
            virtual bool canRead(ConnId id) = 0;
            virtual bool canWrite(ConnId id) = 0;

            virtual ConnId acceptClient() = 0;
            virtual int read(ConnId id, void *buf, std::size_t size) = 0;
            virtual void write(ConnId id, void *data, std::size_t size) = 0;

            virtual unsigned short getServerPort() const = 0;
            virtual const std::string &getServerIp() const = 0;
        protected:
        private:
    };
}
