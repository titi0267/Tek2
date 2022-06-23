/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD11-timothe.coniel
** File description:
** Woody
*/

#include "Woody.hpp"

Woody::Woody(std::string name, std::string file) : Toy(_type, name, file)
{
    _type = WOODY;
    _name = name;
    _picture.getPictureFromFile(file);
}

Woody::~Woody()
{
}
