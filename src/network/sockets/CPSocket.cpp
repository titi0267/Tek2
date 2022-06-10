/*
** EPITECH PROJECT, 2022
** windows-linux-socket
** File description:
** CPSocket
*/

#include "network/CPSocket.hpp"
#ifdef __linux__
    #include "LinuxSocket.hpp"
    #include "../server/LinuxServer.hpp"
    #include "../client/LinuxClient.hpp"
#elif _WIN32
    #include "WinSocket.hpp"
    #include "../server/WinServer.hpp"
    #include "../client/WinClient.hpp"
#endif

std::unique_ptr<network::ISocket> network::CPSocket::createSocket()
{
    #ifdef __linux__
        return (std::make_unique<LinuxSocket>());
    #elif _WIN32
        return (std::make_unique<WinSocket>());
    #endif
    return (nullptr);
}

std::unique_ptr<network::IServer> network::CPSocket::createServer()
{
    #ifdef __linux__
        return (std::make_unique<LinuxServer>());
    #elif _WIN32
        return (std::make_unique<WinServer>());
    #endif
    return (nullptr);
}

std::unique_ptr<network::IClient> network::CPSocket::createClient()
{
    #ifdef __linux__
        return (std::make_unique<LinuxClient>());
    #elif _WIN32
        return (std::make_unique<WinClient>());
    #endif
    return (nullptr);
}