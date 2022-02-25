/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Or
*/

#pragma once
#include "../../include/IComponent.hpp"

class Or {
    public:
        Or();
        nts::Tristate getOr(nts::Tristate a, nts::Tristate b);
        ~Or();

    protected:
    private:
};
