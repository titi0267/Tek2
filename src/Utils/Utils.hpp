/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** Utils
*/

#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <tuple>
#include <regex>
#include "../Error/Error.hpp"

using ChipsetPair = std::tuple<std::string, std::string>;
using LinkPairs = std::tuple<std::string, std::string, std::string, std::string>;

namespace nts {
    class Utils {
        public:
            Utils() = default;
            ~Utils() = default;

            std::string removeNewLine(std::string str);
            std::string removeComments(std::string str);
            int get_space(std::string str, int value);
            bool isValidComponent(std::string value);
            bool isInChipsets(std::vector<ChipsetPair> chipsets, std::string link);
            std::vector<LinkPairs> getLinks(std::vector<std::string> splitedFile);
            std::vector<ChipsetPair> getChipset(std::vector<std::string> splitedFile);
            std::vector<std::string> split(std::string to_split, char token);
            std::string getStrFromFile(const std::string &file);
            std::vector<std::string> getGoodFile(char **av);

        protected:
        private:
    };
}
