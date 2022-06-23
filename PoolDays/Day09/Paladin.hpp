/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD09-timothe.coniel
** File description:
** Paladin
*/

#include "Priest.hpp"
#include "Knight.hpp"

#ifndef PALADIN_HPP_
#define PALADIN_HPP_

class Paladin : public Knight, public Priest
{
    public:
        Paladin(const std::string &name, int power);
        ~Paladin();
        int attack();
        int special();
        void rest();

    protected:
    private:
};

#endif /* !PALADIN_HPP_ */
