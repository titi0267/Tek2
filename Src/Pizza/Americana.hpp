/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Americana
*/

#pragma once
#include "IPizza.hpp"

class Americana: public IPizza {
    public:
        Americana(uint32_t pizzaId, IPizza::PizzaSize size);
        ~Americana();

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
