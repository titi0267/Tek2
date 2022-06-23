/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD10am-timothe.coniel
** File description:
** FruitNode
*/

#include "Fruit.hpp"
#ifndef FRUITNODE_HPP_
#define FRUITNODE_HPP_

typedef struct FruitNode_s {
    Fruit *node;
    struct FruitNode_s *next;
}FruitNode;

#endif /* !FRUITNODE_HPP_ */
