/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** main
*/

#include "Chipsets.hpp"
#include "./include/Components.hpp"
#include "./include/Factory.hpp"


void simulateAll(nts::Factory factory)
{
    for (auto itr : factory.getComp()) {
        itr.simulate(1);
        std::cout << itr.getState()[0] << std::endl;
    }
}

int handleCommand(std::string cmd, nts::Factory facto)
{
    std::regex rgx("(\\w+)=([0-1-U])");

    if (cmd == "exit")
        return 1;
    if (cmd == "simulate")
        simulateAll(facto);
    if (std::regex_match(cmd, rgx))
        facto.setInputValue(cmd);
    return 0;
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 84;
    try {
        nts::Chipsets chipsets(av);
        std::string input;
        nts::Factory factory;

        factory.storeComp(chipsets);
        while (1) {
            std::cout << "> ";
            std::cin >> input;
            if (handleCommand(input, factory) == 1)
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