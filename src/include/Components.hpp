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
            std::unique_ptr<nts::Components> createComponent(const std::string &compType);
            void setComp(int compNumber, std::string compType);
            std::map<std::string, int>::const_iterator nts::Components::getComp(std::string compName) const;
            void nts::Components::newComp();
            int nts::Components::getCompNum() const;

        protected:
            void nts::Components::setName(const std::string &name);
            std::string &nts::Components::getName() const;
            //Pins _pin;

        private:
            std::map<std::string, int> _saveComp;
            int _compNumber;
    };
}
/*
p + (x) = (a-x)/(50 - 150)
pxy = (b - y)/(9b-15)*/