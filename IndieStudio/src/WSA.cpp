/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** WSA
*/

#include "network/sockets/SocketInclude.hpp"
#include "Setup.hpp"


int bomberman::WSA(void)
{
    #ifdef _WIN32
    WSACleanup();
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData))
        return (1);
    #endif
    return (0);
}
