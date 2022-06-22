/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Utils
*/

#pragma once
#include <iostream>
#include "../Pizza/IPizza.hpp"

class Utils {
    public:
        Utils();
        ~Utils();
        bool is_number(const std::string& s);
        IPizza::PizzaType getTypeFromStr(std::string);
        IPizza::PizzaSize getSizeFromStr(std::string);

    protected:
    private:
};
