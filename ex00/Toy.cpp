/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD11-timothe.coniel
** File description:
** Toy
*/

#include "Toy.hpp"
#include "Picture.hpp"

Toy::Toy()
{
    _type = BASIC_TOY;
    setName("toy");
}

Toy::Toy(ToyType type, std::string name, const std::string &file)
{
    _type = type;
    _name = name;
    _picture.getPictureFromFile(file);
}

Toy::~Toy()
{
}

int Toy::getType() const
{
    return _type;
}

std::string Toy::getName() const
{
    return _name;
}


void Toy::setName(std::string name)
{
    _name = name;
}

bool Toy::setAscii(const std::string &file)
{
    return _picture.getPictureFromFile(file);
}

std::string Toy::getAscii() const
{
    return _picture.data;
}
