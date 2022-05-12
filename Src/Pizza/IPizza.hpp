/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Pizza
*/

#pragma once

#include <deque>
#include <iostream>

class IPizza {
    public:
        enum class PizzaType {
            Regina = 1 ,
            Margarita = 2 ,
            Americana = 4 ,
            Fantasia = 8
        };

        enum class PizzaSize {
            S = 1,
            M = 2,
            L = 4,
            XL = 8,
            XXL = 16
        };

        virtual ~IPizza() = default;
        virtual std::deque<std::string> getIngredients() = 0;
        virtual uint32_t getPizzaId() = 0;
        virtual PizzaSize getPizzaSize() = 0;
        virtual uint32_t getBakedTime() = 0;

    protected:
    private:
};
