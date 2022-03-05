/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Components
*/

#pragma once
#include "IComponent.hpp"
#include "Link.hpp"
//#include "../pins/Pins.hpp"

namespace nts {

    class Components : public IComponent
    {
        public:
            Components();
            ~Components();

            nts::Tristate compute(size_t pin);
            void dump() const;
            void simulate(size_t tick); //{};
            void setLink(size_t pin, nts::IComponent &other, size_t otherPin);

            std::string &getType();
            void setState(size_t pin, nts::Tristate state);
            std::vector<nts::Tristate> &getState();
            void setType(std::string type);
            //std::map<size_t, nts::Link *> &getLink();

        protected:
            //void nts::Components::setName(const std::string &name);
            //std::string &nts::Components::getName() const;
            std::map<size_t, nts::Link *> _saveLink;
            std::vector<nts::Tristate> _pins;

        private:
            std::string _type;
    };
};
/*
p + (x) = (a-x)/(50 - 150)
pxy = (b - y)/(9b-15)*/