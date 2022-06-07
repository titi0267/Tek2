/*
** EPITECH PROJECT, 2022
** windows-linux-socket
** File description:
** CPSocket
*/

#include "CPSocket.hpp"
#ifdef __linux__
    #include "LinuxSocket.hpp"
    #include "../server/LinuxServer.hpp"
    #include "../client/LinuxClient.hpp"
#elif _WIN32
    #include "WinSocket.hpp"
    #include "../server/WinServer.hpp"
    #include "../client/WinClient.hpp"
#endif

std::unique_ptr<network::ISocket> network::CPSocket::createSocket(void)
{
    #ifdef __linux__
        return (std::make_unique<LinuxSocket>());
    #elif _WIN32
        return (std::make_unique<WinSocket>());
    #endif
    return (nullptr);
}

std::unique_ptr<network::IServer> network::CPSocket::createServer(const std::string &ip, const std::string &port, const int maxClient)
{
    #ifdef __linux__
        return (std::make_unique<LinuxServer>(ip, port, maxClient));
    #elif _WIN32
        return (std::make_unique<WinServer>(ip, port, maxClient));
    #endif
    return (nullptr);
}

std::unique_ptr<network::IClient> network::CPSocket::createClient(const std::string &ip, const std::string &portString)
{
    #ifdef __linux__
        return (std::make_unique<LinuxClient>(ip, portString));
    #elif _WIN32
        return (std::make_unique<WinClient>(ip, portString));
    #endif
    return (nullptr);
}