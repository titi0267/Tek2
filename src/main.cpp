/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** main
*/

#include "Chipsets.hpp"
#include "./include/Components.hpp"
#include "./include/Factory.hpp"

void display(nts::Factory &factory)
{
    std::cout << "tick: " << factory.getTick() << std::endl;
    std::cout << "input(s):" << std::endl;
    for (auto &itr : factory.getComp()) {
        if (itr.second->getType() == "input")
            std::cout << "  " << itr.first << ": " << ((itr.second->getState()[0] == nts::Tristate::UNDEFINED) ? "U" : std::to_string(itr.second->getState()[0])) << std::endl;
    }
    std::cout << "output(s):" << std::endl;
    for (auto &itr : factory.getComp()) {
        if (itr.second->getType() == "output")
            std::cout << "  " << itr.first << ": " << ((itr.second->getState()[0] == nts::Tristate::UNDEFINED) ? "U" : std::to_string(itr.second->getState()[0])) << std::endl;
    }
}

void simulateAll(nts::Factory &factory)
{
    std::cout << "Set Queue" << std::endl;
    factory.setupQueue();
    factory.setTick(factory.getTick() + 1);
    std::cout << "Start component" << std::endl;
    for (auto &itr : factory.getComp()) {
        std::cout << itr.second->getType() << std::endl;
        std::cout << itr.second->getState()[0] << std::endl;
        itr.second->simulate(1);
    }
    /*
    auto &itr = factory.getComp();
    for (itr.begin();itr != itr.end(); itr++) {
        itr.second->simulate(1);
    }*/
    //std::cout << itr.second->getState()[0] << std::endl;
}

int handleCommand(const std::string &cmd, nts::Factory &facto)
{
    std::regex rgx("(\\w+)=([0-1-U])");

    if (cmd == "exit")
        return 1;
    if (cmd == "simulate") {
        simulateAll(facto);
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