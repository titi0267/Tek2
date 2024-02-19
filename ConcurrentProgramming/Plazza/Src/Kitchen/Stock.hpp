/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Stock
*/

#pragma once
#include <iostream>
#include <cstdint>
#include <deque>

class Stock {
    public:
        enum class Ingredients {
            DOE,
            TOMATO,
            GRUYERE,
            HAM,
            MUSHROOM,
            STEAK,
            EGG,
            GOAT_CHEESE,
            CHIEF_LOVE
        };

        Stock();
        ~Stock();

        void refillAll();
        int takeInStock(Ingredients ingredient);

    protected:
    private:
        std::deque<uint32_t> _ingredients;
};
