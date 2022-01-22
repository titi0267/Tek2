/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD07am-timothe.coniel
** File description:
** Borg
*/

#include "Borg.hpp"

Borg::Ship::Ship()
{
    _side = 300;
    _maxWarp = 9;
    _home = UNICOMPLEX;
    _location = _home;
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
    std::cout << captain->getName() << ": I'm glad to be the captain of the USS " << _name << "." << std::endl;
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
