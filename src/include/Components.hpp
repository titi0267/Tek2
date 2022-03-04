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

            void setComp(std::string compName, std::string type);
            std::string getComp() const;
            void setTick(size_t tick);
            std::string getType() const;
            size_t getTick() const;
            void setState(size_t pin, nts::Tristate state);
            std::vector<nts::Tristate> getState() const;
            

        protected:
            //void nts::Components::setName(const std::string &name);
            //std::string &nts::Components::getName() const;
            std::map<size_t, Link> _saveLink;
            std::string _type;
            std::vector<nts::Tristate> _pins;

        private:
            size_t _tick;
            std::string _name;
    };
};
/*
p + (x) = (a-x)/(50 - 150)
pxy = (b - y)/(9b-15)*/