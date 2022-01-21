/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD07am-timothe.coniel
** File description:
** Federation
*/

#include <iostream>
#include "WarpSystem.hpp"
#ifndef FEDERATION_HPP_
#define FEDERATION_HPP_

namespace Federation {
    namespace Starfleet {
        class Ship {
            public:
                Ship(int length, int width, std::string name, short maxWarp);
                ~Ship();
                void setupCore(WarpSystem::Core *Core_ptr);
                void checkCore();

            protected:
            private:
                int _length;
                int _width;
                std::string _name;
                short _maxWarp;
                WarpSystem::Core *_core;
        };
    };
    class Ship {
        public:
            Ship(int length, int width, std::string name);
            ~Ship();
            void setupCore(WarpSystem::Core *Core_ptr);
            void checkCore();

        protected:
        private:
            int _length;
            int _width;
            std::string _name;
            short _maxWarp;
            WarpSystem::Core *_core;
        };
};

#endif /* !FEDERATION_HPP_ */
