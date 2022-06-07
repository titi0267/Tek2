/*
** EPITECH PROJECT, 2022
** windows-linux-socket
** File description:
** WinSocket
*/

#ifdef _WIN32

#include "WinSocket.hpp"
#include "SocketError.hpp"
#include "SocketInclude.hpp"

network::WinSocket::WinSocket()
{
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == INVALID_SOCKET)
        throw (SocketError("Windows socket()", "function call failed"));
    _socket = (unsigned int)sock;
}

network::WinSocket::~WinSocket()
{
    closesocket(_socket);
}

unsigned int network::WinSocket::getSocket() const
{
    return (_socket);
}

#endif