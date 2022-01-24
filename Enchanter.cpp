/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD09-timothe.coniel
** File description:
** Enchanter
*/

#include "Enchanter.hpp"

Enchanter::Enchanter(const std::string &name, int power) : Peasant(name, power)
{
    std::cout << getName() << " learns magic from his spellbook." << std::endl;
}

Enchanter::~Enchanter()
{
    std::cout << getName() << " closes his spellbook." << std::endl;
}

int Enchanter::attack()
{
    if (_health <= 0) {
        std::cout << getName() << " is out of combat." << std::endl;
        return (0);
    }
    std::cout << getName() << " doesn't know how to fight." << std::endl;
    return (0);
}

int Enchanter::special()
{
    if (_health <= 0) {
        std::cout << getName() << " is out of combat." << std::endl;
        return (0);
    } else if (_power - 50 < 0) {
        std::cout << getName() << " is out of power." << std::endl;
        return (0);
    }
    _power -= 50;
    std::cout << getName() << " casts a fireball." << std::endl;
    return (99);
}

void Enchanter::rest()
{
    if (_health <= 0) {
        std::cout << getName() << " is out of combat." << std::endl;
        return;
    }
    std::cout << getName() << " meditates." << std::endl;
        _power = 100;
}

// int main ( void )
// {
// Enchanter enchanter ("Merlin", 20) ;
// enchanter . attack () ;
// enchanter . special () ;
// enchanter . rest () ;
// enchanter . special () ;
// enchanter . damage (50) ;
// }