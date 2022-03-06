/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Factory
*/

#pragma once
#include "Components.hpp"
#include "IncludeComponents.hpp"
#include "../Chipsets.hpp"

namespace nts {
    class Factory {
        public:
            Factory();
            ~Factory();
            Factory(const Factory &) = delete;

            std::unique_ptr<nts::IComponent> createComponent(const std::string &compType);//, const std::string &name);
            std::map<std::string, std::unique_ptr<nts::IComponent>> &getComp();
            void storeComp(Chipsets comp);
            //int getComponentByName(std::string name);
            void setInputValue(std::string str);
            void setTick(size_t tick);
            size_t getTick() const;
            void addQueue(std::string cmd);
            void setupQueue();

        protected:
            std::map<std::string, std::unique_ptr<nts::IComponent>> _components;
        private:
            size_t _tick;
            std::vector<std::string> _queue;
    };
};
