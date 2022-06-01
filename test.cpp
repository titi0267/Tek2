/*
** EPITECH PROJECT, 2022
** indie
** File description:
** test
*/

#include "Map.hpp"

int main(int ac, char **av)
{
    int height = std::stoi(av[1]);
    int width = std::stoi(av[2]);
    int player = std::stoi(av[3]);
    int complexity = std::stoi(av[4]);
    std::srand(std::time(0));

    try {
        Map test(height, width, player, complexity);
        test.print();
        std::cout << std::endl;
    } catch (std::invalid_argument &e) {
        std::cout << "Construction failed: " << e.what() << std::endl;
    }
}