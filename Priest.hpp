/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD09-timothe.coniel
** File description:
** Priest
*/

#include "Enchanter.hpp"
#ifndef PRIEST_HPP_
#define PRIEST_HPP_

class Priest : public Enchanter
{
    public:
        Priest(const std::string &name, int power);
        ~Priest();
        void rest();

    protected:
    private:
};

#endif /* !PRIEST_HPP_ */
