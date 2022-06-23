/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD11-timothe.coniel
** File description:
** Buzz
*/

#include "Toy.hpp"
#ifndef BUZZ_HPP_
#define BUZZ_HPP_

class Buzz : public Toy {
    public:
        Buzz(std::string type, std::string name = "buzz.txt");
        ~Buzz();
        void speak(std::string statement);

    protected:
    private:
};

#endif /* !BUZZ_HPP_ */
