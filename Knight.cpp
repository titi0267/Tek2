/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD09-timothe.coniel
** File description:
** Knight
*/

#include "Knight.hpp"

Knight::Knight(const std::string& name, int power) : Peasant(name, power)
{
    std::cout << getName() << " vows to protect the kingdom." << std::endl;
}

Knight::~Knight()
{
    std::cout << getName() << " takes off his armor." << std::endl;
}

int Knight::attack()
{
    if (_health <= 0) {
        std::cout << getName() << " is out of combat." << std::endl;
        return (0);
    } else if (_power - 10 < 0) {
        std::cout << getName() << " is out of power." << std::endl;
        return (0);
    }
    std::cout << getName() << " strikes with his sword." << std::endl;
    _power -= 10;
    return (20);
}

int Knight::special()
{
    if (_health <= 0) {
        std::cout << getName() << " is out of combat." << std::endl;
        return (0);
    } else if (_power - 30 < 0) {
        std::cout << getName() << " is out of power." << std::endl;
        return (0);
    }
    _power -= 30;
    std::cout << getName() << " impales his enemy." << std::endl;
    return (50);
}

void Knight::rest()
{
    if (_health <= 0) {
        std::cout << getName() << " is out of combat." << std::endl;
        return;
    }
    _power += 50;
    if (_power > 100)
        _power = 100;
    std::cout << getName() << " eats." << std::endl;
}
