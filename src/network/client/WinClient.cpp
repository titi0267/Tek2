/*
** EPITECH PROJECT, 2022
** windows-linux-socket
** File description:
** Client
*/

#ifdef _WIN32

#include "WinClient.hpp"
#include "../sockets/SocketInclude.hpp"
#include "../sockets/SocketError.hpp"
#include "network/CPSocket.hpp"
#include "network/Utils.hpp"
#include <iostream>

network::WinClient::WinClient()
{
    _connected = false;
}

void network::WinClient::connectTo(const std::string &ip, const std::string &portString)
{
    if (_connected)
        throw (SocketError("WinClient", "client already connected somewhere"));
    _socket = CPSocket::createSocket();
    unsigned port = Utils::portStringToPort(portString);
    struct sockaddr_in serverInfo;

    serverInfo.sin_family = AF_INET;
    serverInfo.sin_port = htons(port);
    if (inet_pton(AF_INET, ip.data(), &(&serverInfo)->sin_addr) != 1)
        throw (SocketError("WinClient", "address given for server creation if ill formated"));
    if (connect(_socket->getSocket(), (struct sockaddr*)&serverInfo, sizeof(serverInfo)) == SOCKET_ERROR)
        throw (SocketError("WinClient", "connect() call failed"));
    _connected = true;
    std::cout << "WinClient successfully connected to server with IP: " << ip << " and Port: "  << port << std::endl;
}

void network::WinClient::disconnect()
{
    if (!_connected)
        throw (SocketError("WinClient", "client is not connected"));
    _connected = false;
    _socket = nullptr;
}

void network::WinClient::updateRWStates()
{
    if (!_connected)
        throw (SocketError("WinClient", "client is not connected"));
    unsigned int socket = _socket->getSocket();
    struct timeval timeout = {0, 1};

    FD_ZERO(&_readSet);
    FD_ZERO(&_writeSet);
    FD_SET(socket, &_readSet);
    FD_SET(socket, &_writeSet);
    if (select(socket + 1, &_readSet, &_writeSet, NULL, &timeout) < 0)
        throw (SocketError("WinClient", "select() call failed"));
}

bool network::WinClient::canRead()
{
    updateRWStates();
    return (FD_ISSET(_socket->getSocket(), &_readSet));
}

bool network::WinClient::canWrite()
{
    updateRWStates();
    return (FD_ISSET(_socket->getSocket(), &_writeSet));
}

int network::WinClient::read(void *buf, std::size_t size)
{
    if (!_connected)
        throw (SocketError("WinClient", "client is not connected"));
    return ::read(_socket->getSocket(), buf, size);
}

//Needs testing
void network::WinClient::write(void *data, std::size_t size)
{
    if (!_connected)
        throw (SocketError("WinClient", "client is not connected"));
    ::write(_socket->getSocket(), data, size);
}

#endif
