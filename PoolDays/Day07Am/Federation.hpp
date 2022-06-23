/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD07am-timothe.coniel
** File description:
** Federation
*/

#include <iostream>
#include "WarpSystem.hpp"
#include "Borg.hpp"
#ifndef FEDERATION_HPP_
#define FEDERATION_HPP_

namespace Federation {
    namespace Starfleet {
        class Captain {
            public:
                Captain(std::string str);
                ~Captain();
                std::string getName();
                int getAge();
                void setAge(int age);

            protected:
            private:
                std::string _name;
                int _age;
        };
        class Ship {
            public:
                Ship(int length, int width, std::string name, short maxWarp, int torpedo = 0);
                Ship();
                ~Ship();
                void setupCore(WarpSystem::Core *Core_ptr);
                void checkCore();
                void promote(Federation::Starfleet::Captain *captain);
                bool move();
                bool move(int warp);
                bool move(Destination d);
                bool move(int warp, Destination d);
                int getShield ();
                void setShield(int shield);
                int getTorpedo();
                void setTorpedo(int torpedo);
                void fire(Borg::Ship *target);
                void fire(int torpedoes, Borg::Ship *target);

            protected:
            private:
                int _length;
                int _width;
                std::string _name;
                short _maxWarp;
                WarpSystem::Core *_core;
                Federation::Starfleet::Captain *_captain;
                Destination _location;
                Destination _home;
                int _shield;
                int _photonTorpedo;
        };
        class Ensign {
            public:
                Ensign(std::string name);
                ~Ensign();

            protected:
            private:
                std::string _name;

        };
    };
    class Ship {
        public:
            Ship(int length, int width, std::string name);
            ~Ship();
            void setupCore(WarpSystem::Core *Core_ptr);
            void checkCore();
            bool move();
            bool move(int warp);
            bool move(Destination d);
            bool move(int warp, Destination d);
            WarpSystem::Core *getCore();

        protected:
        private:
            int _length;
            int _width;
            std::string _name;
            short _maxWarp;
            WarpSystem::Core *_core;
            Destination _location;
            Destination _home;
        };
};

#endif /* !FEDERATION_HPP_ */
