/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD07am-timothe.coniel
** File description:
** Borg
*/

#include "Borg.hpp"
#include "Federation.hpp"

Borg::Ship::Ship(int weaponFrequency = 20 , short repair = 3)
{
    _side = 300;
    _maxWarp = 9;
    _home = UNICOMPLEX;
    _location = _home;
    _shield = 100;
    _weaponFrequency = weaponFrequency;
    _repair = repair;
    std::cout << "We are the Borgs. Lower your shields and surrender yourselves unconditionally." << std::endl;
    std::cout << "Your biological characteristics and technologies will be assimilated." << std::endl;
    std::cout << "Resistance is futile." << std::endl;
}

Borg::Ship::~Ship()
{
    ;
}

void Borg::Ship::setupCore(WarpSystem::Core *Core_ptr)
{
    _core = Core_ptr;
}

void Borg::Ship::checkCore()
{
    std::string str;

    if (_core->checkReactor()->isStable() == true)
        std::cout << "Everything is in order." << std::endl;
    else
        std::cout << "Critical failure imminent." << std::endl;
}

WarpSystem::Core *Federation::Ship::getCore()
{
    return _core;
}

void Borg::Ship::fire(Federation::Starfleet::Ship *target)
{
    target->setShield(target->getShield() - _weaponFrequency);
    std::cout << "Firing on target with " << _weaponFrequency << "GW frequency .";
}

void Borg::Ship::fire(Federation::Ship *target)
{
    target->getCore()->checkReactor()->setStability(false);
}

void Borg::Ship::repair()
{
    if (_repair > 0) {
        _repair -= 1;
        setShield(100);
        std::cout << "Begin shield re-initialisation... Done. Awaiting further instructions." << std::endl;
    } else
        std::cout << "Energy cells depleted, shield weakening.";
}


bool Borg::Ship::move(int warp, Destination d)
{
    if (warp <= _maxWarp && d != _location && _core->checkReactor()->isStable() == true) {
    _location = d;
    return true;
    }
    return false;
}

bool Borg::Ship::move(int warp)
{
    if (warp <= _maxWarp && _core->checkReactor()->isStable() == true) {
        _location = _home;
        return true;
    }
    return false;
}

bool Borg::Ship::move(Destination d)
{
    if (d != _location && _core->checkReactor()->isStable() == true) {
        _location = d;
        return true;
    }
    return false;
}

bool Borg::Ship::move()
{
    if (_core->checkReactor()->isStable() == true) {
        _location = _home;
        return true;
    }
    return false;
}

int Borg::Ship::getShield()
{
    return _shield;
}

void Borg::Ship::setShield(int shield)
{
    _shield = shield;
}

int Borg::Ship::getWeaponFrequency()
{
    return _weaponFrequency;
}

void Borg::Ship::setWeaponFrequency(int frequency)
{
    _weaponFrequency = frequency;
}

short Borg::Ship::getRepair()
{
    return _repair;
}

void Borg::Ship::setRepair(short repair)
{
    _repair = repair;
}

Federation::Starfleet::Captain::Captain(std::string str)
{
    _name = str;
    _age = 0;
}

Federation::Starfleet::Captain::~Captain()
{
    ;
}

std::string Federation::Starfleet::Captain::getName()
{
    return (_name);
}

int Federation::Starfleet::Captain::getAge()
{
    return (_age);
}

void Federation::Starfleet::Captain::setAge(int age)
{
    _age = age;
}

void Federation::Starfleet::Ship::promote(Captain *captain)
{
    _captain = captain;
    std::cout << _captain->getName() << ": I'm glad to be the captain of the USS " << _name << "." << std::endl;
}

Federation::Starfleet::Ensign::Ensign(std::string name)
{
    _name = name;
    std::cout << "Ensign " << _name << ", awaiting orders." << std::endl;
}

Federation::Starfleet::Ensign::~Ensign()
{
    ;
}
