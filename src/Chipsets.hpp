/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** chipsets
*/

#pragma once
#include "nano.hpp"

class Chipsets
{
private:
    std::tuple<std::string, std::string> *_inputs;
    std::tuple<std::string, std::string> *_outputs;
    std::tuple<std::string, std::string> *_clocks;
    std::tuple<std::string, std::string> *_trues;
    std::tuple<std::string, std::string> *_falses;
    std::tuple<std::string, std::string> *_components;
    std::tuple<std::string, std::string, std::string, std::string> *_links;
public:
    Chipsets(char **av);
    ~Chipsets();
    std::tuple<std::string, std::string> *getInputs();
    std::tuple<std::string, std::string> *getOutputs();
    std::tuple<std::string, std::string> *getClocks();
    std::tuple<std::string, std::string> *getTrues();
    std::tuple<std::string, std::string> *getFalses();
    std::tuple<std::string, std::string> *getLogicComponents();
    std::tuple<std::string, std::string, std::string, std::string> *getChipsetLinks();
};
