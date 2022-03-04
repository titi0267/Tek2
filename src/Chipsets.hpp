/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** chipsets
*/

#pragma once

#include "Utils/Utils.hpp"
#include "Error/Error.hpp"
#include "include/IComponent.hpp"

using ChipsetPair = std::tuple<std::string, std::string>;
using LinkPairs = std::tuple<std::string, std::string, std::string, std::string>;

namespace nts {

    class Chipsets {
    private:
        std::vector<ChipsetPair> _inputs;
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
        std::vector<ChipsetPair> getInputs();
        std::vector<ChipsetPair> getOutputs();
        std::vector<ChipsetPair> getClocks();
        std::vector<ChipsetPair> getTrues();
        std::vector<ChipsetPair> getFalses();
        std::vector<ChipsetPair> getLogicComponents();
        std::vector<LinkPairs> getChipsetLinks();
        std::vector<ChipsetPair> getComponents(std::vector<ChipsetPair> chipsets, std::string word);
        std::vector<ChipsetPair> getInputComponents(std::vector<ChipsetPair> chipsets);
        void checkLinks(std::vector<LinkPairs> links, std::vector<ChipsetPair> chipsets);
    };
}