/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** Simulate
*/

#pragma once

#include "../include/Factory.hpp"

namespace nts {
    class Simulate {
        public:
            Simulate() = delete;
            ~Simulate() = delete;

            static void simulateLoop(nts::Factory &factory);
        protected:
        private:
    };
};