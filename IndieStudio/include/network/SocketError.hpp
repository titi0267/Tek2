/*
** EPITECH PROJECT, 2022
** windows-linux-socket
** File description:
** SocketError
*/

#pragma once

#include <exception>
#include <string>

namespace network {
    class SocketError : public std::exception {
        public:
            SocketError(const std::string &type, const std::string &message);
            const char *what() const noexcept override;
            ~SocketError();
        protected:
            std::string _message;
        private:
    };
}
