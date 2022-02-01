/*
** EPITECH PROJECT, 2022
** core.cpp for Rush3 Epitech 2025
** File description:
** core
*/

#include "core.hpp"

int main(int ac, char **av, char **env)
{
    if (ac == 1) {
        Window b;
        b.printWindow();
    } else {
        ncursesMain();
    }
    return (0);
}
