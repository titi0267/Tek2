/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD09-timothe.coniel
** File description:
** Peasant
*/

#include <iostream>
#include "ICharacter.hpp"
#ifndef PEASANT_HPP_
#define PEASANT_HPP_

class Peasant : public ICharacter
{
    public:
        Peasant(const std::string& name, int power);
        ~Peasant();
        const std::string &getName() const;
        int getPower() const;
        int getHp() const;
        int attack();
        int special();
        void rest();
        void damage(int damage);

    protected:
        std::string _name;
        int _power;
        int _health = 100;
    private:

};

#endif /* !PEASANT_HPP_ */
