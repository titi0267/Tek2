/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** chipsets
*/

#include "Chipsets.hpp"

std::vector<ChipsetPair> nts::Chipsets::getLogic(std::vector<ChipsetPair> chipsets)
{
    std::string tmp = "";
    std::vector<ChipsetPair> comp;
    auto itr = std::begin(chipsets);

    for (; itr != std::end(chipsets); ++itr) {
        tmp = std::get<0>(*itr);
        if (isdigit(tmp[0])) {
            if (!tools.isValidComponent(tmp))
                throw Error("Component doesn't exist");
            comp.push_back(std::make_tuple(tmp, std::get<1>(*itr)));
        }
    }
    return comp;
}

std::vector<ChipsetPair> nts::Chipsets::getComponents(std::vector<ChipsetPair> chipsets, std::string word)
{
    std::string tmp = "";
    std::vector<ChipsetPair> inputs;
    auto itr = std::begin(chipsets);

    for (; itr != std::end(chipsets); ++itr) {
        tmp = std::get<0>(*itr);
        if (tmp == word)
            inputs.push_back(std::make_tuple(tmp, std::get<1>(*itr)));
    }
    return inputs;
}

void nts::Chipsets::checkLinks(std::vector<LinkPairs> links, std::vector<ChipsetPair> chipsets)
{
    std::string firstValue = "";
    std::string secondValue = "";
    auto itr = std::begin(links);

    for (; itr != std::end(links); ++itr) {
        firstValue = std::get<0>(*itr);
        secondValue = std::get<2>(*itr);
        if (!tools.isInChipsets(chipsets, firstValue) || !tools.isInChipsets(chipsets, secondValue))
            throw Error("Invalid Link");
    }
}

nts::Chipsets::Chipsets(char **av)
{
    std::string tmp = "a";
    std::vector<std::string> goodFile = tools.getGoodFile(av);
    std::vector<ChipsetPair> chipset = tools.getChipset(goodFile);
    std::vector<LinkPairs> links = tools.getLinks(goodFile);

    checkLinks(links, chipset);
    _inputs = getComponents(chipset, "input");
    _outputs = getComponents(chipset, "output");
    _clocks = getComponents(chipset, "clock");
    _trues = getComponents(chipset, "true");
    _falses = getComponents(chipset, "false");
    _components = getLogic(chipset);
    _links = links;
}

nts::Chipsets::~Chipsets()
{
    ;
}

std::vector<ChipsetPair>  nts::Chipsets::getInputs()
{
    return  _inputs;
}

std::vector<ChipsetPair>  nts::Chipsets::getOutputs()
{
    return _outputs;
}

std::vector<ChipsetPair>  nts::Chipsets::getClocks()
{
    return _clocks;
}

std::vector<ChipsetPair>  nts::Chipsets::getTrues()
{
    return _trues;
}

std::vector<ChipsetPair>  nts::Chipsets::getFalses()
{
    return _falses;
}

std::vector<ChipsetPair>  nts::Chipsets::getLogicComponents()
{
    return _components;
}

std::vector<LinkPairs> nts::Chipsets::getChipsetLinks()
{
    return _links;
}