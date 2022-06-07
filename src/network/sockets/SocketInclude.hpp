/*
** EPITECH PROJECT, 2022
** windows-linux-socket
** File description:
** SocketInclude
*/

#pragma once

#ifdef __linux__
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <sys/socket.h>
#elif _WIN32
    #define _WINSOCK_DEPRECATED_NO_WARNINGS
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #include <io.h>
    #pragma comment(lib, "Ws2_32.lib")
#endif
