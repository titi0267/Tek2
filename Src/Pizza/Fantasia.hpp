/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Fantasia
*/

#pragma once
#include "IPizza.hpp"

class Fantasia: public IPizza {
    public:
        Fantasia(uint32_t pizzaId, IPizza::PizzaSize size);
        ~Fantasia();

        std::deque<std::string> getIngredients();
        uint32_t getPizzaId();
        IPizza::PizzaSize getPizzaSize();
        uint32_t getBakedTime();

    protected:
    private:
        uint32_t _id;
        std::deque<std::string> _ingredients;
        IPizza::PizzaSize _size;
        uint32_t _bakedTime;
};
