/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD11-timothe.coniel
** File description:
** Buzz
*/

#include "Buzz.hpp"

Buzz::Buzz(std::string name, std::string file) : Toy(_type, name, file)
{
    _type = BUZZ;
    _name = name;
    _picture.getPictureFromFile(file);
}

Buzz::~Buzz()
{
}

void Buzz::speak(std::string statement)
{
    std::cout << "BUZZ: " << getName() << " \"" << statement << "\"" << std::endl;
}