/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Link
*/

#pragma once
#include "./IComponent.hpp"

namespace nts {
    class Link {
        public:
            Link(IComponent &comp, size_t p);
            ~Link();

            IComponent &component;
            size_t pin;
    };
};