/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD08-timothe.coniel
** File description:
** Droid
*/

#include "Droid.hpp"

Droid::Droid(std::string serial)
{
    _Id = serial;
    _Energy = 50;
    _Status = new std::string("Standing by");
    std::cout << "Droid '" << _Id << "' Activated" << std::endl;

}

Droid::Droid(Droid &copy)
{
    _Id = copy.getId();
    _Energy = copy.getEnergy();
    _Status = copy.getStatus();
    std::cout << "Droid '" << _Id << "' Activated, Memory Dumped" << std::endl;
}

Droid::~Droid()
{
    std::cout << "Droid '" << _Id << "' Destroyed" << std::endl;
}

void Droid::setId(std::string serial)
{
    _Id = serial;
}

std::string Droid::getId()
{
    return _Id;
}

void Droid::setEnergy(size_t Energy)
{
    _Energy = Energy;
    if (Energy > 100)
        _Energy = 100;
}

size_t Droid::getEnergy()
{
    return _Energy;
}

const size_t Droid::getAttack()
{
    return _Attack;
}

const size_t Droid::getToughness()
{
    return _Toughness;
}

void Droid::setStatus(std::string *stat)
{
    delete(_Status);
    _Status = new std::string(*stat);
}

std::string *Droid::getStatus()
{
    return _Status;
}

void Droid::operator=(Droid &other)
{
    delete(_Status);
    _Status = new std::string(*(other._Status));
    _Id = other._Id;
    _Energy = other._Energy;
}

bool Droid::operator==(Droid &other)
{
    if ((_Id == other.getId()) && (_Energy == other.getEnergy()) && (_Status == other.getStatus()))
        return (true);
    return (false);
}

bool Droid::operator!=(Droid &other)
{
    return !operator==(other);
}

Droid &Droid::operator<<(size_t &energy)
{
    int nb = 100 - _Energy;

    _Energy += energy;
    if (energy > nb)
        energy -= nb;
    else
        energy = 0;
    if (_Energy > 100)
        _Energy = 100;
    if (_Energy < 0)
        _Energy = 0;
    return (*this);
}

std::ostream &operator<<(std::ostream &os, Droid &other)
{
    return (os << "Droid '" << other.getId() << "', " << *(other.getStatus()) << ", " << other.getEnergy());
}

int main ()
{
Droid d ;
Droid d1 (" Avenger ") ;
size_t Durasel = 200;
std :: cout << d << std :: endl ;
std :: cout << d1 << std :: endl ;
d = d1 ;
d . setStatus (new std :: string (" Kill Kill Kill !") ) ;
d << Durasel ;
std :: cout << d << " --" << Durasel << std :: endl ;
Droid d2 = d ;
d . setId ("Rex") ;
std :: cout << ( d2 != d ) << std :: endl ;
return 0;
}