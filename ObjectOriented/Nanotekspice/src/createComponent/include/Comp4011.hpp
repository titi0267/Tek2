/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Comp4011
*/

#pragma once
#include "../../include/Components.hpp"

namespace nts {
    class Comp4011 : public Components
    {
        public:
            Comp4011();
            ~Comp4011();

            Tristate compute(size_t pin);
            void setLink(size_t pin, nts::IComponent &other, size_t otherPin);
            void simulate(size_t tick);
            void dump() const;
        protected:
        private:
    };
};