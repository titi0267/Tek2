/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD07am-timothe.coniel
** File description:
** Borg
*/


#include <iostream>
#include "Destination.hpp"
#include "WarpSystem.hpp"
#ifndef BORG_HPP_
#define BORG_HPP_

namespace Federation {
    namespace Starfleet {
        class Ship;
    };
    class Ship;
};

namespace Borg {
    class Ship {
        public:
            Ship(int weaponFrequency = 20, short repair = 3);
            ~Ship();
            void checkCore();
            void setupCore(WarpSystem::Core *Core_ptr);
            bool move();
            bool move(int warp);
            bool move(Destination d);
            bool move(int warp, Destination d);
            int getShield();
            void setShield(int shield);
            int getWeaponFrequency();
            void setWeaponFrequency(int frequency);
            short getRepair();
            void setRepair(short repair);
            void fire(Federation::Starfleet::Ship *target);
            void fire (Federation::Ship *target);
            void repair();

        protected:
        private:
        int _side;
        short _maxWarp;
        WarpSystem::Core *_core;
        Destination _location;
        Destination _home;
        int _shield; // set to 100 upon construction
        int _weaponFrequency; // provided upon construction
        short _repair; // can be provided . if not , set to 3 upon construction
    };
};

#endif /* !BORG_HPP_ */
