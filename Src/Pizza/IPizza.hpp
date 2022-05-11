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
        virtual ~IPizza() = 0;
        virtual std::deque<std::string> getIngredients() = 0;
        virtual int getPizzaNbr() = 0;
        virtual int getPizzaSize() = 0;

    protected:
    private:
};
