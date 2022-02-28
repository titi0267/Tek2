/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Components
*/

#pragma once
#include "IComponent.hpp"

class Components : public nts::IComponent
{
    public:
        Components();
        ~Components();

    protected:
        std::vector<nts::Tristate> create4081();
    private:
};
