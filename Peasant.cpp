/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD09-timothe.coniel
** File description:
** Peasant
*/

#include "Peasant.hpp"

Peasant::Peasant(const std::string &name, int power)
{
    _name = name;
    if (power > 100)
        _power = 100;
    else
        _power = power;
    std::cout << _name << " goes for an adventure." << std::endl;
}

Peasant::~Peasant()
{
    std::cout << _name << " is back to his crops." << std::endl;
}

const std::string &Peasant::getName() const
{
    return _name;
}

int Peasant::getPower() const
{
    return _power;
}

int Peasant::getHp() const
{
    return _health;
}

int Peasant::attack()
{
    if (_power - 10 < 0) {
        std::cout << getName() << " is out of power." << std::endl;
        return (0);
    } else if (_health <= 0) {
        std::cout << getName() << " is out of combat." << std::endl;
        return (0);
    }
    std::cout << getName() << " tosses a stone." << std::endl;
    _power -= 10;
    return (5);
}

int Peasant::special()
{
    if (_health <= 0) {
        std::cout << getName() << " is out of combat." << std::endl;
        return (0);
    }
    std::cout << getName() << " doesn't know any special move." << std::endl;
    return (0);
}

void Peasant::rest()
{
    if (_health <= 0) {
        std::cout << getName() << " is out of combat." << std::endl;
        return;
    }
    std::cout << getName() << " takes a nap." << std::endl;
    if (_power + 30 >= 100)
        _power = 100;
    else
        _power += 30;
}

void Peasant::damage(int damage)
{
    _health -= damage;
    if (_health > 0)
        std::cout << _name << " takes " << damage << " damage." << std::endl;
    if (_health <= 0) {
        std::cout << _name << " is out of combat." << std::endl;
        _health = 0;
        return;
    }
}

//int main(void)
//{
//Peasant peasant ("Gildas", 42) ;
//peasant . damage (50) ;
//peasant . damage (100) ;
//peasant . damage (200) ;
//peasant . rest () ;
//}