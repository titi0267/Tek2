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
            static std::unique_ptr<ISocket> createSocket();
            static std::unique_ptr<IServer> createServer();
            static std::unique_ptr<IClient> createClient();

        protected:
        private:
    };
}
