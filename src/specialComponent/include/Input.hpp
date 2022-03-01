/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Input
*/

#pragma once
#include "../../include/Components.hpp"
#include "../../pins/Pins.hpp"

namespace nts {
    class Input : public Components
    {
        public:
            Input(size_t key);
            ~Input();

            Tristate compute(size_t pin);
        protected:
        private:
    };
}