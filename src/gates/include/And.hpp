/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** And
*/

#pragma once
#include "../../include/IComponent.hpp"
#include "../../include/Gates.hpp"

class And : public Gates
{
    public:
        And();
        nts::Tristate getAnd(std::vector<nts::Tristate> a, std::vector<nts::Tristate> b);
        ~And();

    protected:
    private:
};
