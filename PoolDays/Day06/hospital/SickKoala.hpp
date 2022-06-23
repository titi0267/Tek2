/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD06-timothe.coniel
** File description:
** SickKoala
*/

#include <iostream>

#ifndef SICKKOALA_HPP_
#define SICKKOALA_HPP_

class SickKoala {
    public:
        SickKoala(std::string name);
        ~SickKoala();
        void poke(void);
        bool takeDrug(std::string str);
        void overDrive(std::string str);
        std::string name;
};

#endif /* !SICKKOALA_HPP_ */
