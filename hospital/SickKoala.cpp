/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD06-timothe.coniel
** File description:
** SickKoala
*/

#include <iostream>
#include "SickKoala.hpp"

SickKoala::SickKoala(std::string str)
{
    name = str;
}

SickKoala::~SickKoala()
{
    std::cout << "Mr." << name << ": Kreooogg!! I'm cuuuured!" << std::endl;
}

void SickKoala::poke(void)
{
    std::cout << "Mr." << name << ": Gooeeeeerrk!!" << std::endl;
}

bool SickKoala::takeDrug(std::string str)
{
    if (str == "Mars") {
        std::cout << "Mr." << name << ": Mars, and it kreogs!" << std::endl;
        return (true);
    }
    else if (str == "Kinder") {
        std::cout << "Mr." << name << ": There is a toy inside!" << std::endl;
        return (true);
    }
    std::cout << "Mr." << name << ": Goerkreog!" << std::endl;
    return (false);
}

void SickKoala::overDrive(std::string str)
{
    std::cout << "Mr." << name << ":";
    size_t pos = str.find("Kreog!");

    while (pos != std::string::npos) {
        str.replace(pos, 6,"1337!");
        pos = str.find("Kreog!", pos + 5);
    }
    std::cout << str << std::endl;
}
