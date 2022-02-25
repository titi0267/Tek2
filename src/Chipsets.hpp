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
public:
    Chipsets(char **av);
    ~Chipsets();
};
