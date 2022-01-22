/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD07am-timothe.coniel
** File description:
** Borg
*/


#include <iostream>
#include "Federation.hpp"
#ifndef BORG_HPP_
#define BORG_HPP_

namespace Borg {
    class Ship {
        public:
            Ship();
            ~Ship();
            void checkCore();
            void setupCore(WarpSystem::Core *Core_ptr);

        protected:
        private:
        int _side;
        short _maxWarp;
        WarpSystem::Core *_core;
    };
};

#endif /* !BORG_HPP_ */
