/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Margarita
*/

#pragma once
#include "IPizza.hpp"

class Margarita: public IPizza {
    public:
        Margarita(uint32_t pizzaId, IPizza::PizzaSize size);
        ~Margarita();

        std::deque<bool> getIngredients();
        uint32_t getPizzaId();
        IPizza::PizzaSize getPizzaSize();
        uint32_t getBakedTime();

    protected:
    private:
        uint32_t _id;
        std::deque<bool> _ingredients;
        IPizza::PizzaSize _size;
        uint32_t _bakedTime;
};
