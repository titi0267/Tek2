/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD07pm-timothe.coniel
** File description:
** Skat
*/

#include <iostream>
#ifndef SKAT_HPP_
#define SKAT_HPP_

class Skat
{
    public:
        Skat(const std::string &name = "bob", int stimPaks = 15);
        ~ Skat();
        int &stimPaks() ;
        const std::string &name();
        void shareStimPaks(int number, int &stock);
        void addStimPaks(unsigned int number);
        void useStimPaks();
        void status();
    private:
        std::string _name;
        int _stimPaks;
};

#endif /* !SKAT_HPP_ */
