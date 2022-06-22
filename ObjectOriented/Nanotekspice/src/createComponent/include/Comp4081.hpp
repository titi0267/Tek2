/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** 4081And
*/

#pragma once
#include "../../include/Components.hpp"

namespace nts {
    class Comp4081 : public Components
    {
        public:
            Comp4081();
            ~Comp4081();

            Tristate compute(size_t pin);
            void dump() const;
            void simulate(size_t tick);
            void setLink(size_t pin, nts::IComponent &other, size_t otherPin);

        protected:
        private:
    };
}