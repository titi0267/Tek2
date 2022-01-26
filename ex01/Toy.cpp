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

Toy& Toy::operator=(const Toy& toy)
{
    _type = toy._type;
    _name = toy._name;
    _picture = toy._picture;
    return (*this);
}
/*
int main ()
{
Toy toto;
Toy ET(Toy::ALIEN, "green", "./alien.txt") ;
toto.setName("TOTO!");
if ( toto . getType () == Toy::BASIC_TOY)
std::cout << "basic toy: " << toto.getName() << std::endl
<< toto . getAscii () << std :: endl ;
if ( ET . getType () == Toy::ALIEN)
std::cout << " this alien is: " << ET.getName() << std::endl
<< ET.getAscii() << std::endl;
return 0;
}*/