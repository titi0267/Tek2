/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD09-timothe.coniel
** File description:
** Priest
*/

#include "Priest.hpp"

Priest::Priest(const std::string &name, int power) : Peasant::Peasant(name,power),Enchanter(name,power)
{
    std::cout << getName() << " enters in the order." << std::endl;
}

Priest::~Priest()
{
    std::cout << getName() << " finds peace." << std::endl;
}

void Priest::rest()
{
    if (_health <= 0) {
        std::cout << getName() << " is out of combat." << std::endl;
        return;
    }
    _health = 100;
    _power = 100;
    std::cout << getName() << " prays." << std::endl;
}

//int main ( void )
//{
//Priest priest ("Trichelieu", 20) ;
//priest . attack () ;
//priest . special () ;
//priest . rest () ;
//priest . damage (50) ;
//}