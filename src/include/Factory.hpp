/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Factory
*/

#pragma once
#include "Components.hpp"
#include "../Chipsets.hpp"

namespace nts {
    class Factory {
        public:
            Factory();
            ~Factory();

            std::unique_ptr<nts::Components> createComponent(const std::string &compType, const std::string &name);
            void newComp();
            int getCompNum() const;
            std::vector<nts::Components> getComp() const;
            void storeComp(Chipsets comp);
            int getComponentByName(std::string name);
            void setInputValue(std::string str);

        protected:
            std::vector<nts::Components> _components;
        private:
            int _compNumber;
    };
}
