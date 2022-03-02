/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** main
*/

#include "Chipsets.hpp"

int handleCommand(std::string cmd, nts::Chipsets *chipset)
{
    std::regex rgx("(\\w+)=([0-1-U])");

    if (cmd == "exit")
        return 1;
    if (std::regex_match(cmd, rgx))
        chipset->setInputValue(cmd);
    return 0;
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 84;
    try {
        nts::Chipsets chipsets(av);
        std::string input;

        while (1) {
            std::cout << "> ";
            std::cin >> input;
            if (handleCommand(input, &chipsets) == 1)
                return 0;
        }
    } catch (Error e) {
        std:: cerr << e.what() << std::endl;
        return 84;
    } catch (...) {
        std::cerr << "Unknown error" << std::endl;
        return 84;
    }
    return (0);
}