/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** main
*/

#include "Chipsets.hpp"
#include "./include/Components.hpp"
#include "./include/Factory.hpp"
#include "./Simulate/Simulate.hpp"

void display(nts::Factory &factory)
{
    std::cout << "tick: " << factory.getTick() << std::endl;
    std::cout << "input(s):" << std::endl;
    for (auto &itr : factory.getComp()) {
        if (itr.second->getType() == "input")
            std::cout << "  " << itr.first << ": " << ((itr.second->getState()[0] == nts::Tristate::UNDEFINED) ? "U" : std::to_string(itr.second->getState()[0])) << std::endl;
        if (itr.second->getType() == "clock")
            std::cout << "  " << itr.first << ": " << ((itr.second->getState()[0] == nts::Tristate::UNDEFINED) ? "U" : std::to_string(itr.second->getState()[0])) << std::endl;
    }
    std::cout << "output(s):" << std::endl;
    for (auto &itr : factory.getComp()) {
        if (itr.second->getType() == "output")
            std::cout << "  " << itr.first << ": " << ((itr.second->getState()[0] == nts::Tristate::UNDEFINED) ? "U" : std::to_string(itr.second->getState()[0])) << std::endl;
    }
}

int handleCommand(const std::string &cmd, nts::Factory &facto)
{
    std::regex rgx("(\\w+)=([0-1-U])");

    if (cmd == "exit")
        return 1;
    if (cmd == "simulate") {
        nts::Simulate::simulateLoop(facto);
        return (0);
    }
    if (cmd == "display") {
        display(facto);
        return (0);
    }
    if (std::regex_match(cmd, rgx)) {
        facto.addQueue(cmd);
        return (0);
    }
    std::cout << "Command not found\n";
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
        std::cout << "> ";
        while (std::getline(std::cin, input)) {
            if (handleCommand(input, factory) == 1)
                return 0;
            std::cout << "> ";
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