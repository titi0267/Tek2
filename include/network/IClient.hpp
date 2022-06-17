/*
** EPITECH PROJECT, 2022
** windows-linux-socket
** File description:
** IClient
*/

#pragma once

#include <vector>
#include <string>

namespace network {
    class IClient {
        public:
        virtual ~IClient() = default;

        virtual void connectTo(const std::string &ip, const std::string &portString) = 0;
        virtual void disconnect() = 0;

        virtual void updateRWStates() = 0;

        virtual bool canRead() = 0;
        virtual bool canWrite() = 0;

        virtual int read(void *buf, std::size_t size) = 0;
        virtual void write(void *data, std::size_t size) = 0;

        virtual bool isConnected() = 0;
    };
}
