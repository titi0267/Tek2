/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD11-timothe.coniel
** File description:
** Woody
*/

#include "Toy.hpp"
#ifndef WOODY_HPP_
#define WOODY_HPP_

class Woody : public Toy {
    public:
        Woody(std::string name, std::string file = "woody.txt");
        ~Woody();

    protected:
    private:
};

#endif /* !WOODY_HPP_ */
