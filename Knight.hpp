/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD09-timothe.coniel
** File description:
** Knight
*/

#include "Peasant.hpp"
#ifndef KNIGHT_HPP_
#define KNIGHT_HPP_

class Knight : virtual public Peasant
{
    public:
        Knight(const std::string& name, int power);
        ~Knight();
        int attack();
        int special();
        void rest();

    protected:
    private:
};

#endif /* !KNIGHT_HPP_ */
