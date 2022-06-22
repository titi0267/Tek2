/*
** EPITECH PROJECT, 2022
** windows-linux-socket
** File description:
** ISocket
*/

#pragma once

namespace network {
    class ISocket {
        public:
            virtual ~ISocket() = default;
            virtual unsigned int getSocket() const = 0;
        protected:
        private:
    };
}
