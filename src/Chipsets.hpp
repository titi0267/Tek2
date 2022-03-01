/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** chipsets
*/

#pragma once

#include "Utils/Utils.hpp"
#include "Error/Error.hpp"
#include "IComponent.hpp"

using ChipsetPair = std::tuple<std::string, std::string>;
using LinkPairs = std::tuple<std::string, std::string, std::string, std::string>;
using InputPair = std::tuple<std::string, std::string, nts::Tristate>;

namespace nts {

    class Chipsets {
    private:
        std::vector<InputPair> _inputs;
        std::vector<ChipsetPair> _outputs;
        std::vector<ChipsetPair> _clocks;
        std::vector<ChipsetPair> _trues;
        std::vector<ChipsetPair> _falses;
        std::vector<ChipsetPair> _components;
        std::vector<LinkPairs> _links;
    public:
        Utils tools;
        Chipsets(char **av);
        ~Chipsets();
        std::vector<ChipsetPair> getLogic(std::vector<ChipsetPair> chipsets);
        std::vector<InputPair> getInputs();
        std::vector<ChipsetPair> getOutputs();
        std::vector<ChipsetPair> getClocks();
        std::vector<ChipsetPair> getTrues();
        std::vector<ChipsetPair> getFalses();
        std::vector<ChipsetPair> getLogicComponents();
        std::vector<LinkPairs> getChipsetLinks();
        void setInputValue(std::string str);
        std::vector<ChipsetPair> getComponents(std::vector<ChipsetPair> chipsets, std::string word);
        std::vector<InputPair> getInputComponents(std::vector<ChipsetPair> chipsets);
        void checkLinks(std::vector<LinkPairs> links, std::vector<ChipsetPair> chipsets);
    };
}