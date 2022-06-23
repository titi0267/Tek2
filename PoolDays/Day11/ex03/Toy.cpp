/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD11-timothe.coniel
** File description:
** Toy
*/

#include <iostream>
#include <memory>

#include "Toy.hpp"
#include "Buzz.hpp"
#include "Woody.hpp"
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

Toy& Toy::operator=(const Toy& toy)
{
    _type = toy._type;
    _name = toy._name;
    _picture = toy._picture;
    return (*this);
}

void Toy::speak(std::string statement)
{
    std::cout << getName() << " \"" << statement << "\"" <<  std::endl;
}

// int main ()
// {
// std :: unique_ptr < Toy > b (new Buzz ("buzziiiii") ) ;
// std :: unique_ptr < Toy > w (new Woody ("wood") ) ;
// std :: unique_ptr < Toy > t (new Toy ( Toy :: ALIEN , "ET", "alien .txt") ) ;
// b->speak("To the code, and beyond!!!!!!!!") ;
// w->speak("There's a snake in my boot.") ;
// t->speak("the claaaaaaw ") ;
// }