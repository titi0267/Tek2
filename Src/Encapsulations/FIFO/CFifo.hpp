/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** CFifo
*/

#pragma once

#include <sys/types.h>
#include <sys/stat.h>
#include <poll.h>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include "../../Pizza/SendPizza.hpp"

namespace IPC {
    class ParentToChild {
        public:
            ParentToChild(int Id);
            ~ParentToChild();
            ParentToChild(const ParentToChild &) = delete;
            void CMakeFifo();
            void COpenFifoRead();
            void COpenFifoWrite();
            SendPizza_t *CReadFifo();
            void CCloseRd();
            void CCloseWr();
            void CWriteFifo(SendPizza_t *pizzaInfo);
            bool test_poll();
        protected:
        private:
            SendPizza_t _messageRead;
            struct pollfd _poll;
            int _fdRd;
            int _fdWr;
            char _PToC[30];
        };
    class ChildToParent {
        public:
            ChildToParent(int Id);
            ~ChildToParent();
            ChildToParent(const ChildToParent &) = delete;
            void CMakeFifo();
            void COpenFifoRead();
            void COpenFifoWrite();
            uint32_t CReadFifo();
            void CCloseRd();
            void CCloseWr();
            void CWriteFifo(uint32_t Id);
            bool test_poll();
        protected:
        private:
            struct pollfd _poll;
            uint32_t _messageRead;
            int _fdRd;
            int _fdWr;
            char _CToP[30];
    };
};