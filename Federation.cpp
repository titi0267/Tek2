/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD07am-timothe.coniel
** File description:
** Federation
*/

#include "Federation.hpp"
#include "Borg.hpp"

Federation::Starfleet::Ship::Ship(int length, int width, std::string name, short maxWarp, int torpedo)
{
    _length = length;
    _width = width;
    _name = name;
    _maxWarp = maxWarp;
    _home = EARTH;
    _location = _home;
    _shield = 100;
    _photonTorpedo = torpedo;
    std::cout << "The ship USS " << _name << " has been finished." << std::endl;
    std::cout << "It is " << _length << " m in length and " << _width << " m in width." << std::endl;
    std::cout << "It can go to Warp " << _maxWarp << "!" << std::endl;
    if (_photonTorpedo == 0)
        std::cout << "Weapons are set: " <<_photonTorpedo << " torpedoes ready.";
}

Federation::Starfleet::Ship::Ship()
{
    _length = 289;
    _width = 132;
    _maxWarp = 6;
    _home = EARTH;
    _location = _home;
    _shield = 100;
    _photonTorpedo = 0;
    _name = "Entreprise";
    std::cout << "The ship USS " << _name << " has been finished." << std::endl;
    std::cout << "It is " << _length << " m in length and " << _width << " m in width." << std::endl;
    std::cout << "It can go to Warp " << _maxWarp << "!" << std::endl;
}

Federation::Starfleet::Ship::~Ship()
{
    ;
}

void Federation::Starfleet::Ship::setupCore(WarpSystem::Core *Core_ptr)
{
    _core = Core_ptr;
    std::cout << "USS " << _name << ": The core is set." << std::endl;
}

void Federation::Starfleet::Ship::checkCore()
{
    std::string str;

    if (_core->checkReactor()->isStable() == true)
        str = "stable";
    else
        str = "unstable";
    std::cout << "USS " << _name << ": The core is " << str <<  " at the time." << std::endl;
}

void Federation::Ship::checkCore()
{
    std::string str;

    if (_core->checkReactor()->isStable() == true)
        str = "stable";
    else
        str = "unstable";
    std::cout << _name << ": The core is " << str <<  " at the time." << std::endl;
}

void Federation::Ship::setupCore(WarpSystem::Core *Core_ptr)
{
    _core = Core_ptr;
    std::cout << _name << ": The core is set." << std::endl;
}

Federation::Ship::Ship(int length, int width, std::string name)
{
    _length = length;
    _width = width;
    _name = name;
    _maxWarp = 1;
    _home = VULCAN;
    _location = _home;
    std::cout << "The independent ship " << _name << " just finished its construction." << std::endl;
    std::cout << "It is " << _length << " m in length and " << _width << " m in width." << std::endl;
}

Federation::Ship::~Ship()
{
    ;
}

bool Federation::Ship::move(int warp, Destination d)
{
    if (warp <= _maxWarp && d != _location && _core->checkReactor()->isStable() == true) {
    _location = d;
    return true;
    }
    return false;
}

bool Federation::Ship::move(int warp)
{
    if (warp <= _maxWarp && _core->checkReactor()->isStable() == true) {
        _location = _home;
        return true;
    }
    return false;
}

bool Federation::Ship::move(Destination d)
{
    if (d != _location && _core->checkReactor()->isStable() == true) {
        _location = d;
        return true;
    }
    return false;
}

bool Federation::Ship::move()
{
    if (_core->checkReactor()->isStable() == true) {
        _location = _home;
        return true;
    }
    return false;
}

bool Federation::Starfleet::Ship::move(int warp, Destination d)
{
    if (warp <= _maxWarp && d != _location && _core->checkReactor()->isStable() == true) {
        _location = d;
        return true;
    }
    return false;
}

bool Federation::Starfleet::Ship::move(int warp)
{
    if (warp <= _maxWarp && _core->checkReactor()->isStable() == true) {
        _location = _home;
        return true;
    }
    return false;
}

bool Federation::Starfleet::Ship::move(Destination d)
{
    if (d != _location && _core->checkReactor()->isStable() == true) {
        _location = d;
        return true;
    }
    return false;
}

bool Federation::Starfleet::Ship::move()
{
    if (_core->checkReactor()->isStable() == true) {
        _location = _home;
        return true;
    }
    return false;
}

int Federation::Starfleet::Ship::getShield()
{
    return _shield;
}

void Federation::Starfleet::Ship::setShield(int shield)
{
    _shield = shield;
}

int Federation::Starfleet::Ship::getTorpedo()
{
    return _photonTorpedo;
}

void Federation::Starfleet::Ship::setTorpedo(int torpedo)
{
    _photonTorpedo = torpedo;
}

void Federation::Starfleet::Ship::fire(Borg::Ship *target)
{
    if (_photonTorpedo > 1) {
        _photonTorpedo -= 1;
        target->setShield(target->getShield()-1);
        std::cout << _name << ": Firing on target. " << _photonTorpedo << " torpedoes remaining.";
    } else if (_photonTorpedo == 1) {
        _photonTorpedo -= 1;
        target->setShield(target->getShield()-1);
        std::cout << _name << ": No more torpedo to fire, " << _captain->getName() << "!";
    } else {
        std::cout << _name << ": No enough torpedoes to fire, " << _captain->getName() << "!";
    }
}

void Federation::Starfleet::Ship::fire(int torpedoes, Borg::Ship *target)
{
    if (_photonTorpedo > torpedoes) {
        _photonTorpedo -= torpedoes;
        target->setShield(target->getShield() - (50 * torpedoes));
        std::cout << _name << ": Firing on target. " << _photonTorpedo << " torpedoes remaining.";
    } else if (_photonTorpedo == torpedoes) {
        _photonTorpedo -= torpedoes;
        target->setShield(target->getShield() - (50 * torpedoes));
        std::cout << _name << ": No more torpedo to fire, " << _captain->getName() << "!";
    } else {
        std::cout << _name << ": No enough torpedoes to fire, " << _captain->getName() << "!";
    }
}
