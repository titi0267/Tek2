/*
** EPITECH PROJECT, 2022
** windows-linux-socket
** File description:
** LinuxSocket
*/

#ifdef __linux__

#include "LinuxSocket.hpp"
#include "SocketError.hpp"
#include "SocketInclude.hpp"

network::LinuxSocket::LinuxSocket()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0)
        throw (SocketError("Linux socket", "socket() call failed"));
    _socket = (unsigned int)sock;
}

network::LinuxSocket::~LinuxSocket()
{
    close(_socket);
}

unsigned int network::LinuxSocket::getSocket() const
{
    return (_socket);
}

#endif
