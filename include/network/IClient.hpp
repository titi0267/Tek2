/*
** EPITECH PROJECT, 2022
** windows-linux-socket
** File description:
** IClient
*/

#pragma once

#include <vector>

namespace network {
    class IClient {
        public:
            virtual ~IClient() = default;

            virtual void updateRWStates() = 0;

            virtual bool canRead() = 0;
            virtual bool canWrite() = 0;

            virtual int read(void *buf, std::size_t size) = 0;
            virtual void write(void *data, std::size_t size) = 0;

        protected:
        private:
    };
}
