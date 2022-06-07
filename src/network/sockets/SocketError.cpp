/*
** EPITECH PROJECT, 2022
** windows-linux-socket
** File description:
** SocketError
*/

#include "SocketError.hpp"

network::SocketError::SocketError(const std::string &type, const std::string &message)
{
    _message = "sockets: Caught an error of type \"";
    _message.append(type);
    _message.append("\": \"");
    _message.append(message);
    _message.append("\"");
}

network::SocketError::~SocketError()
{
}

const char *network::SocketError::what() const noexcept
{
    return (_message.data());
}