/*
** EPITECH PROJECT, 2022
** windows-linux-socket
** File description:
** CPSocket
*/

#pragma once

#include <memory>
#include "ISocket.hpp"
#include "network/IServer.hpp"
#include "network/IClient.hpp"

namespace network {
    class CPSocket {
        public:
            CPSocket() = default;
            ~CPSocket() = default;
            static std::unique_ptr<ISocket> createSocket(void);
            static std::unique_ptr<IServer> createServer(const std::string &ip = "", const std::string &port = "", const int maxClient = 4);
            static std::unique_ptr<IClient> createClient(const std::string &ip = "0.0.0.0", const std::string &portString = "");

        protected:
        private:
    };
}
