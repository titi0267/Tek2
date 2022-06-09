/*
** EPITECH PROJECT, 2022
** windows-linux-socket
** File description:
** Server
*/

#ifdef _WIN32

#include "WinServer.hpp"
#include "../sockets/SocketError.hpp"
#include "../sockets/SocketInclude.hpp"
#include "network/CPSocket.hpp"
#include "network/Utils.hpp"
#include <iostream>
#include <vector>
#include <fstream>

network::WinServer::WinServer()
{
    _created = false;
}

void network::WinServer::createServer(const std::string &ip, const std::string &portString, const int maxClient)
{
    if (_created)
        throw (SocketError("WinServer", "server already has been created"));
    _socket = CPSocket::createSocket();
    unsigned short port = Utils::portStringToPort(portString);
    struct sockaddr_in serverInfo;
    unsigned int socket = _socket->getSocket();

    _port = port;
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_port = htons(port);
    if (ip.empty())
        serverInfo.sin_addr.s_addr = INADDR_ANY;
    else
        if (inet_pton(AF_INET, ip.data(), &(&serverInfo)->sin_addr) != 1)
            throw (SocketError("WinServer", "address given for server creation is ill formated"));
    if (bind(socket, (struct sockaddr *)&serverInfo, sizeof(serverInfo)))
        throw (SocketError("WinServer", "bind() call failed"));
    if (listen(socket, maxClient))
        throw (SocketError("WinServer", "listen() call failed"));
    if (!_port)
        setPortFromSocket();
    _ip = ip.empty() ? findIp() : ip;
    _created  = true;
    std::cout << "WinServer created successfully with IP: " << _ip << " and Port: "  << _port << std::endl;
}

void network::WinServer::closeServer()
{
    if (!_created)
        throw (SocketError("WinServer", "server has not been created"));
    _socket = nullptr;
    _created = false;
}

void network::WinServer::setPortFromSocket()
{
    struct sockaddr_in sin;
    socklen_t len = sizeof(sin);

    if (getsockname(_socket->getSocket(), (struct sockaddr *)&sin, &len) == -1)
        throw (SocketError("WinServer", "getsockname() call when getting the port failed"));
    _port = ntohs(sin.sin_port);
}

void network::WinServer::updateRWStates()
{
    if (!_created)
        throw (SocketError("WinServer", "server has not been created"));
    unsigned int socket = _socket->getSocket();
    struct timeval timeout = {0, 1};
    int fdMax = 0;

    FD_ZERO(&_readSet);
    FD_ZERO(&_writeSet);
    FD_SET(socket, &_readSet);
    if (socket > fdMax)
        fdMax = socket;
    for (unsigned int i = 0; i < _clients.size(); i++) {
        FD_SET(_clients[i], &_readSet);
        FD_SET(_clients[i], &_writeSet);
        if (_clients[i] > fdMax)
            fdMax = _clients[i];
    }
    if (select(fdMax + 1, &_readSet, &_writeSet, NULL, &timeout) < 0)
        throw (SocketError("WinServer", "select() call failed"));
}

bool network::WinServer::canAcceptConn()
{
    updateRWStates();
    return (FD_ISSET(_socket->getSocket(), &_readSet));
}

bool network::WinServer::canRead(ConnId id)
{
    updateRWStates();
    return (FD_ISSET(_clients[id], &_readSet));
}

bool network::WinServer::canWrite(ConnId id)
{
    updateRWStates();
    return (FD_ISSET(_clients[id], &_writeSet));
}

network::ConnId network::WinServer::acceptClient()
{
    if (!_created)
        throw (SocketError("WinServer", "server has not been created"));
    static ConnId id = 0;
    SocketFd clientFd = 0;
    struct sockaddr_in clientAddr;
    socklen_t size = sizeof(clientAddr);

    clientFd = accept(_socket->getSocket(), (struct sockaddr *) &clientAddr, &size);
    if (clientFd == -1)
        throw (SocketError("LinuxServer", "accept() call failed"));
    std::cout << "Connection from " << inet_ntoa(clientAddr.sin_addr) <<":" << ntohs(clientAddr.sin_port) << std::endl;
    _clients.insert({id, clientFd});
    return (id++);
}

//Needs testing
int network::WinServer::read(ConnId id, void *buf, std::size_t size)
{
    if (!_created)
        throw (SocketError("WinServer", "server has not been created"));
    SocketFd fd = _clients[id];

    return ::read(fd, buf, size);
}

//Needs testing
void network::WinServer::write(ConnId id, void *data, std::size_t size)
{
    if (!_created)
        throw (SocketError("WinServer", "server has not been created"));
    SocketFd fd = _clients[id];

    ::write(fd, data, size);
}

//#warning WinServer::disconnectConn() may not be correct !
void network::WinServer::disconnectConn(ConnId conn)
{
    closesocket(_clients[conn]);
    _clients.erase(conn);
}

//TODO//
std::string network::WinServer::findIp()
{
    std::ifstream ifs;

    system("ipconfig > ip");
    ifs.open("ip", std::ifstream::in);
    for (std::string line; std::getline(ifs, line); ) {
        if (line.find("IPv4") != std::string::npos) {
            line.erase(0, line.find_last_of(":") + 2);
            return (line);
        }
    }
    return (std::string("0.0.0.0"));
}

#endif
