/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD10am-timothe.coniel
** File description:
** Fruit
*/

#include <iostream>
#ifndef FRUIT_HPP_
#define FRUIT_HPP_

class Fruit {
    public:
        Fruit();
        ~Fruit();
        std::string getName();
        int getVitamins();

    protected:
        int _vitamins = 0;
        std::string _fruit = "";
    private:
};

#endif /* !FRUIT_HPP_ */
