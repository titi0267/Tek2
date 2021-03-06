/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD07pm-timothe.coniel
** File description:
** Skat
*/

#include "Skat.hpp"
#include <iostream>

Skat::Skat(const std::string &name, int stimPaks)
{
    _name = name;
    _stimPaks = stimPaks;
}

Skat::~Skat()
{
    ;
}

int &Skat::stimPaks()
{
    return _stimPaks;
}

const std::string &Skat::name()
{
    return _name;
}

void Skat::shareStimPaks(int number, int &stock)
{
    if (number > _stimPaks) {
        std::cout << "Don't be greedy" << std::endl;
        return;
    }
    stock += number;
    _stimPaks -= number;
    std::cout << "Keep the change." << std::endl;
}

void Skat::addStimPaks(unsigned int number)
{
    _stimPaks += number;
    if (number == 0)
        std::cout << "Hey boya, did you forget something?";
}

void Skat::useStimPaks()
{
    if (_stimPaks > 0) {
        std::cout << "Time to kick some ass and chew bubble gum." << std::endl;
        _stimPaks--;
    }
    else
        std::cout << "Mediiiiiic" << std::endl;
}

void Skat::status()
{
    std::cout << "Soldier " << _name << " reporting " << _stimPaks << " stimpaks remaining sir!" << std::endl;
}
