/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD07am-timothe.coniel
** File description:
** Federation
*/

#include "Federation.hpp"

Federation::Starfleet::Ship::Ship(int length, int width, std::string name, short maxWarp)
{
    _length = length;
    _width = width;
    _name = name;
    _maxWarp = maxWarp;
    _home = EARTH;
    _location = _home;
    std::cout << "The ship USS " << name << " has been finished." << std::endl;
    std::cout << "It is " << length << " m in length and " << width << " m in width." << std::endl;
    std::cout << "It can go to Warp " << maxWarp << "!" << std::endl;
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