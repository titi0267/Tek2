/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD09-timothe.coniel
** File description:
** Enchanter
*/

#include "Peasant.hpp"
#ifndef ENCHANTER_HPP_
#define ENCHANTER_HPP_

class Enchanter : public Peasant
{
    public:
        Enchanter(const std::string &name, int power);
        ~Enchanter();
        int attack();
        int special();
        void rest();

    protected:
    private:
};

#endif /* !ENCHANTER_HPP_ */
