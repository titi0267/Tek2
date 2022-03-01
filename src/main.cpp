/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** main
*/

#include "Chipsets.hpp"

void handleCommand(std::string cmd)
{
    if (cmd == "exit")
        exit(0);
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 84;
    try {
        nts::Chipsets chipsets(av);
    } catch (Error e) {
        std:: cerr << e.what() << std::endl;
        return 84;
    } catch (...) {
        std::cerr << "Unknown error" << std::endl;
        return 84;
    }
    // while (1) {
    //     std::cout << "> ";
    //     std::cin >> input;
    //     handleCommand(input);
    // }
    return (0);
}