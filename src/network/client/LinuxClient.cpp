/*
** EPITECH PROJECT, 2022
** windows-linux-socket
** File description:
** Client
*/

#ifdef __linux__

#include "LinuxClient.hpp"
#include "../sockets/SocketInclude.hpp"
#include "../sockets/SocketError.hpp"
#include "network/CPSocket.hpp"
#include "network/Utils.hpp"
#include <iostream>

network::LinuxClient::LinuxClient()
{
    _connected = false;
}

void network::LinuxClient::connectTo(const std::string &ip, const std::string &portString)
{
    if (_connected)
        throw (SocketError("LinuxClient", "client already connected somewhere"));
    _socket = CPSocket::createSocket();
    unsigned port = Utils::portStringToPort(portString);
    struct sockaddr_in serverInfo;

    serverInfo.sin_family = AF_INET;
    serverInfo.sin_port = htons(port);
    if (inet_pton(AF_INET, ip.data(), &(&serverInfo)->sin_addr) != 1)
        throw (SocketError("LinuxClient", "address given for server creation if ill formated"));
    if (connect(_socket->getSocket(), (struct sockaddr *) &serverInfo, sizeof(serverInfo)))
        throw (SocketError("LinuxClient", "connect() call failed"));
    _connected = true;
    std::cout << "LinuxClient successfully connected to server with IP: " << ip << " and Port: "  << port << std::endl;
}

void network::LinuxClient::disconnect()
{
    if (!_connected)
        throw (SocketError("LinuxClient", "client is not connected"));
    _connected = false;
    _socket = nullptr;
}

void network::LinuxClient::updateRWStates()
{
    if (!_connected)
        throw (SocketError("LinuxClient", "client is not connected"));
    unsigned int socket = _socket->getSocket();
    struct timeval timeout = {0, 1};

    FD_ZERO(&_readSet);
    FD_ZERO(&_writeSet);
    FD_SET(socket, &_readSet);
    FD_SET(socket, &_writeSet);
    if (select(socket + 1, &_readSet, &_writeSet, NULL, &timeout) < 0)
        throw (SocketError("LinuxClient", "select() call failed"));
}

bool network::LinuxClient::canRead()
{
    updateRWStates();
    return (FD_ISSET(_socket->getSocket(), &_readSet));
}

bool network::LinuxClient::canWrite()
{
    updateRWStates();
    return (FD_ISSET(_socket->getSocket(), &_writeSet));
}

int network::LinuxClient::read(void *buf, std::size_t size)
{
    if (!_connected)
        throw (SocketError("WinClient", "client is not connected"));
    return ::read(_socket->getSocket(), buf, size);
}

//Needs testing
void network::LinuxClient::write(void *data, std::size_t size)
{
    if (!_connected)
        throw (SocketError("WinClient", "client is not connected"));
    ::write(_socket->getSocket(), data, size);
}

#endif
