/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Output
*/

#pragma once
#include "../../include/Components.hpp"
#include "../../pins/Pins.hpp"

namespace nts {
    class Output : public Components
    {
        public:
            Output(size_t key, std::string name);
            ~Output();

            Tristate compute(size_t pin);
            void dump() const;
            void setLink(size_t pin, nts::IComponent &other, size_t otherPin);
        protected:
        private:
    };
}
