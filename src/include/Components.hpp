/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Components
*/

#pragma once
#include "IComponent.hpp"
#include "../pins/Pins.hpp"

namespace nts {
    class Components : public IComponent
    {
        public:
            Components();
            ~Components();

            virtual nts::Tristate compute(size_t pin) = 0;
            virtual void dump() const = 0;
        /*std::unique_ptr<nts::IComponent> createComponent(const std::string &str) {
            if (str == "4001")
                return std::make_unique<C4001>();
            else if ...*/
        

        protected:
            void nts::Components::setName(std::string name);
            std::string nts::Components::getName() const;
            Pins _pin;
            int component_number;
            //std::vector<nts::Tristate> create4081();
        private:
            std::string _compName;
    };
}
/*
p + (x) = (a-x)/(50 - 150)
pxy = (b - y)/(9b-15)*/