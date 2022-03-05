/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Gates
*/

#pragma once

#include "../include/IComponent.hpp"

namespace nts {
    class Gates
    {
        public:
            Gates() = delete;
            ~Gates() = delete;

            static Tristate And(Tristate a, Tristate b);
            static Tristate Not(Tristate a);
            static Tristate Xor(Tristate a, Tristate b);
            static Tristate Nand(Tristate a, Tristate b);
            static Tristate Or(Tristate a, Tristate b);
            static Tristate Nor(Tristate a, Tristate b);
    };
}