/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** chipsets
*/

#include "Chipsets.hpp"

std::tuple<std::string, std::string> *getLogic(std::tuple<std::string, std::string> *chipsets)
{
    int len = 0;
    int h = 0;
    int j = 0;
    std::string tmp = "a";

    for (int i = 0; tmp != ""; i++) {
        tmp = std::get<0>(chipsets[i]);
        if (isdigit(tmp[0])) {
            if (!isValidComponent(tmp))
                exit(84);
            len++;
        }
    }
    tmp = "a";
    std::tuple<std::string, std::string> *comp = new std::tuple<std::string, std::string>[len + 1];
        for (; tmp != ""; h++) {
        tmp = std::get<0>(chipsets[h]);
        if (isdigit(tmp[0])) {
            comp[j] = std::make_tuple(tmp, std::get<1>(chipsets[h]));
            j++;
        }
    }
    comp[j] = std::make_tuple("", "");
    return comp;
}

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

void checkLinks(std::tuple<std::string, std::string, std::string, std::string> *links, std::tuple<std::string, std::string> *chipsets)
{
    std::string firstValue = "a";
    std::string secondValue = "";

    for (int i = 0; firstValue != ""; i++) {
        firstValue = std::get<0>(links[i]);
        secondValue = std::get<2>(links[i]);
        if (!isInChipsets(chipsets, firstValue) || !isInChipsets(chipsets, secondValue))
            exit(84);
    }
}

Chipsets::Chipsets(char **av)
{
    std::string tmp = "a";
    std::vector<std::string> goodFile = getGoodFile(av);
    std::tuple<std::string, std::string> *chipset = getChipset(goodFile);
    std::tuple<std::string, std::string, std::string, std::string> *links = getLinks(goodFile);

    checkLinks(links, chipset);
    _inputs = getComponents(chipset, "input");
    _outputs = getComponents(chipset, "output");
    _clocks = getComponents(chipset, "clock");
    _trues = getComponents(chipset, "true");
    _falses = getComponents(chipset, "false");
    _components = getLogic(chipset);
    _links = links;
}

Chipsets::~Chipsets()
{
}

std::tuple<std::string, std::string> *Chipsets::getInputs()
{
    return  _inputs;
}

std::tuple<std::string, std::string> *Chipsets::getOutputs()
{
    return _outputs;
}

std::tuple<std::string, std::string> *Chipsets::getClocks()
{
    return _clocks;
}

std::tuple<std::string, std::string> *Chipsets::getTrues()
{
    return _trues;
}

std::tuple<std::string, std::string> *Chipsets::getFalses()
{
    return _falses;
}

std::tuple<std::string, std::string> *Chipsets::getLogicComponents()
{
    return _components;
}

std::tuple<std::string, std::string, std::string, std::string> *Chipsets::getChipsetLinks()
{
    return _links;
}