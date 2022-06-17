/*
** EPITECH PROJECT, 2022
** windows-linux-socket
** File description:
** Utils
*/

#pragma once

#include <string>
#include <stdexcept>

namespace network {
    class Utils {
        public:
            Utils() = delete;

            static unsigned short portStringToPort(const std::string &portStr)
            {
                unsigned short port = 4243;

                if (portStr.empty())
                    return (port);
                try {
                    unsigned long i = std::stoul(portStr);
                    if (i > 65535)
                        throw (std::invalid_argument("Number too big to be a port"));
                    port = (unsigned short) i;
                } catch (std::invalid_argument const&) {
                    throw (SocketError("Server", "port given for server creation is ill formated"));
                }

                return (port);
            }
        protected:
        private:
    };
}
