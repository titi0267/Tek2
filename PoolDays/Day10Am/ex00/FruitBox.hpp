/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD10am-timothe.coniel
** File description:
** FruitBox
*/

#include "Fruit.hpp"
#include "FruitNode.hpp"

#ifndef FRUITBOX_HPP_
#define FRUITBOX_HPP_

class FruitBox {
    public:
        FruitBox(int size);
        ~FruitBox();
        int nbFruits();
        bool putFruit(Fruit *f);
        Fruit *pickFruit();

    protected:
    private:
        int _size;
        FruitNode *front_ptr;
};

#endif /* !FRUITBOX_HPP_ */
