/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-tekspice-ludovic.sutter
** File description:
** nano
*/

#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <tuple>
#include <regex>

void check_error(std::vector<std::string>);
std::vector<std::string> split(std::string to_split, char token);
std::tuple<std::string, std::string> *getChipset(std::vector<std::string> splitedFile);
std::tuple<std::string, std::string, std::string, std::string> *getLinks(std::vector<std::string> splitedFile);
