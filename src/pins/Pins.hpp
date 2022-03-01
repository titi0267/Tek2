/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Pins
*/

#pragma once
#include "../include/IComponent.hpp"

namespace nts {
    class Pins {
        public:
            Pins();
            ~Pins();

            Tristate Pins::getPin(std::size_t key);
            void Pins::setPin(std::size_t key, Tristate state);
        protected:
        private:
            std::map<std::size_t, Tristate> _pin;
    };
}