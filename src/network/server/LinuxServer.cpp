/*
** EPITECH PROJECT, 2022
** windows-linux-socket
** File description:
** Server
*/

#ifdef __linux__

#include "LinuxServer.hpp"
#include "../sockets/SocketError.hpp"
#include "../sockets/SocketInclude.hpp"
#include "network/CPSocket.hpp"
#include "network/Utils.hpp"
#include <iostream>
#include <vector>
#include <fstream>

network::LinuxServer::LinuxServer(const std::string &ip, const std::string &portString, const int maxClient)
{
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
            throw (SocketError("LinuxServer", "address given for server creation is ill formated"));
    if (bind(socket, (struct sockaddr *)&serverInfo, sizeof(serverInfo)))
        throw (SocketError("LinuxServer", "bind() call failed"));
    if (listen(socket, maxClient))
        throw (SocketError("LinuxServer", "listen() call failed"));
    if (!_port)
        setPortFromSocket();
    _ip = ip.empty() ? findIp() : ip;
    std::cout << "LinuxServer created successfully with IP: " << _ip << " and Port: "  << _port << std::endl;
}

void network::LinuxServer::setPortFromSocket()
{
    struct sockaddr_in sin;
    socklen_t len = sizeof(sin);

    if (getsockname(_socket->getSocket(), (struct sockaddr *)&sin, &len) == -1)
        throw (SocketError("LinuxServer", "getsockname() call when getting the port failed"));
    _port = ntohs(sin.sin_port);
}

void network::LinuxServer::updateRWStates()
{
    unsigned int socket = _socket->getSocket();
    struct timeval timeout = {0, 1};
    int fdMax = 0;

    FD_ZERO(&_readSet);
    FD_ZERO(&_writeSet);
    FD_SET(socket, &_readSet);
    if (socket > fdMax)
        fdMax = socket;
    for (auto &[conn, socket] : _clients) {
        FD_SET(socket, &_readSet);
        FD_SET(socket, &_writeSet);
        if (socket > fdMax)
            fdMax = socket;
    }
    if (select(fdMax + 1, &_readSet, &_writeSet, NULL, &timeout) < 0)
        throw (SocketError("LinuxServer", "select() call failed"));
}

bool network::LinuxServer::canAcceptConn()
{
    updateRWStates();
    return (FD_ISSET(_socket->getSocket(), &_readSet));
}

bool network::LinuxServer::canRead(ConnId id)
{
    updateRWStates();
    return (FD_ISSET(_clients[id], &_readSet));
}

bool network::LinuxServer::canWrite(ConnId id)
{
    updateRWStates();
    return (FD_ISSET(_clients[id], &_writeSet));
}

network::ConnId network::LinuxServer::acceptClient()
{
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
int network::LinuxServer::read(ConnId id, void *buf, std::size_t size)
{
    SocketFd fd = _clients[id];

    return ::read(fd, buf, size);
}

//Needs testing
void network::LinuxServer::write(ConnId id, void *data, std::size_t size)
{
    SocketFd fd = _clients[id];

    ::write(fd, data, size);
}

void network::LinuxServer::disconnectConn(ConnId conn)
{
    close(_clients[conn]);
    _clients.erase(conn);
}

//Needs testing on other computer
std::string network::LinuxServer::findIp()
{
    std::ifstream ifs;
    std::string line;

    system("hostname -i | awk '{print $1}' > ip" );
    ifs.open("ip", std::ifstream::in);
    std::getline(ifs, line);
    return (line);
}

#endif
