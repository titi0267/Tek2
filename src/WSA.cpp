/*
** EPITECH PROJECT, 2022
** indie
** File description:
** WSA
*/

#include "network/sockets/SocketInclude.hpp"

int WSA(void)
{
    #ifdef _WIN32
    WSACleanup();
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData))
        return (84);
    return (0);
    #endif
}
