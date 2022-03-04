/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Components
*/

#pragma once
#include "IComponent.hpp"
//#include "../pins/Pins.hpp"

namespace nts {

    struct Link {
        IComponent &component;
        size_t pin;
    };

    class Components : public IComponent
    {
        public:
            Components();
            ~Components();

            nts::Tristate compute(size_t pin);
            void dump() const;
            void simulate(size_t tick); //{};
            void setLink(size_t pin, nts::IComponent &other, size_t otherPin);

            std::string getType() const;
            void setState(size_t pin, nts::Tristate state);
            std::vector<nts::Tristate> getState() const;
            void setType(std::string type);
            

        protected:
            //void nts::Components::setName(const std::string &name);
            //std::string &nts::Components::getName() const;
            std::map<size_t, Link> _saveLink;
            std::vector<nts::Tristate> _pins;

        private:
            std::string _type;
    };
};
/*
p + (x) = (a-x)/(50 - 150)
pxy = (b - y)/(9b-15)*/