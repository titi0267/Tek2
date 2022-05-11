/*
** EPITECH PROJECT, 2022
** plaza
** File description:
** plaza
*/

#include <iostream>

#include "Reception/Reception.hpp"
#include "Error/Error.hpp"

int main(int ac, char **av)
{
    try {
        Reception reception(ac, av);
    } catch (Error e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }
    return (0);
}