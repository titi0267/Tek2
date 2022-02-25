/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** chipsets
*/

#include "Chipsets.hpp"

std::tuple<std::string, std::string> *getComponents(std::tuple<std::string, std::string> *chipsets, std::string word)
{
    int len = 0;
    int h = 0;
    int j = 0;
    std::string tmp = "a";

    for (int i = 0; tmp != ""; i++) {
        tmp = std::get<0>(chipsets[i]);
        if (tmp == word)
            len++;
    }
    tmp = "a";
    std::tuple<std::string, std::string> *inputs = new std::tuple<std::string, std::string>[len + 1];
    for (; tmp != ""; h++) {
        tmp = std::get<0>(chipsets[h]);
        if (tmp == word) {
            inputs[j] = std::make_tuple(tmp, std::get<1>(chipsets[h]));
            j++;
        }
    }
    inputs[j] = std::make_tuple("", "");
    return inputs;
}

Chipsets::Chipsets(char **av)
{
    std::vector<std::string> goodFile = getGoodFile(av);
    std::tuple<std::string, std::string> *chipset = getChipset(goodFile);

    _inputs = getComponents(chipset, "input");
    _outputs = getComponents(chipset, "output");
    _clocks = getComponents(chipset, "clock");
    _trues = getComponents(chipset, "true");
    _falses = getComponents(chipset, "false");
}

Chipsets::~Chipsets()
{
}