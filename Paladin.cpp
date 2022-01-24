/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD09-timothe.coniel
** File description:
** Paladin
*/

#include "Paladin.hpp"

Paladin::Paladin(const std::string &name, int power) : Peasant::Peasant(name,power), Knight::Knight(name,power) , Priest::Priest(name,power)
{
    std::cout << Knight::getName() << " fights for the light." << std::endl;
}

Paladin::~Paladin()
{
    std::cout << Knight::getName() << " is blessed." << std::endl;
}

//int main ( void )
//{
//Paladin paladin("Uther", 99) ;
//paladin.attack() ;
//paladin.special() ;
//paladin.rest() ;
//paladin.damage(50) ;
//}