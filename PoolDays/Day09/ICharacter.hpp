/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD09-timothe.coniel
** File description:
** ICharacter
*/

#include <iostream>
#include <string>
#ifndef ICHARACTER_HPP_
#define ICHARACTER_HPP_

class ICharacter
{
    public:
        virtual ~ICharacter() = default;
        virtual const std::string &getName() const = 0;
        virtual int getPower() const = 0;
        virtual int getHp() const = 0;
        virtual int attack() = 0;
        virtual int special() = 0;
        virtual void rest() = 0;
        virtual void damage(int damage) = 0;

    protected:
    private:
};

#endif /* !ICHARACTER_HPP_ */
