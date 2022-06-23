/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD06-timothe.coniel
** File description:
** KoalaNurse
*/

#include <iostream>
#include "SickKoala.hpp"
#include <fstream>

#ifndef KOALANURSE_HPP_
#define KOALANURSE_HPP_

class KoalaNurse {
    public:
        KoalaNurse(int num_id);
        ~KoalaNurse();
        void giveDrug(std::string str, SickKoala *s_koala);
        std::string readReport(std::string str);
        void timeCheck(void);
        int id;
        bool working;
};

#endif /* !KOALANURSE_HPP_ */
