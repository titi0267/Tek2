/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD10am-timothe.coniel
** File description:
** FruitBox
*/

#include "FruitBox.hpp"
#include "FruitNode.hpp"
#include "Banana.hpp"
#include "Lemon.hpp"

FruitBox::FruitBox(int size)
{
    FruitNode *node = new(FruitNode);
    front_ptr = NULL;
    node->node = nullptr;
    node->next = NULL;
        for (int i = 0; i != size; i++) {
        node->node = nullptr;
        node->next = front_ptr;
        front_ptr = node;
        node = new (FruitNode);
    }
}

FruitBox::~FruitBox()
{
    FruitNode *elem = new(FruitNode);

    for (;front_ptr != NULL && elem != NULL; front_ptr = elem) {
        elem = front_ptr->next;
        delete(front_ptr);
    }
}

int FruitBox::nbFruits()
{
    int len = 0;
    FruitNode *fruits = front_ptr;

    for (; fruits != NULL; fruits = fruits->next) {
        if (fruits->node != nullptr) {
            len++;
        }
    }
    return (len);
}

bool FruitBox::putFruit(Fruit *f)
{
    FruitNode *elem = front_ptr;

    for (; elem != NULL; elem = elem->next) {
        if (elem->node == nullptr) {
            elem->node = f;
            return (true);
        }
    }
    return (false);
}

Fruit *FruitBox::pickFruit()
{
    FruitNode *elem = front_ptr;
    Fruit *fruit;

    for (; elem != NULL; elem = elem->next) {
        if (elem->node != nullptr) {
            fruit = elem->node;
            elem->node = nullptr;
            return fruit;
        }
    }
    return nullptr;
}
