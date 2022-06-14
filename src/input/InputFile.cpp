/*
** EPITECH PROJECT, 2022
** input
** File description:
** InputFile
*/

#include "InputFile.hpp"
#include "KeyboardBind.hpp"
#include "GamepadBind.hpp"
#include <fstream>
#include <iostream>
#include <regex>
#include <filesystem>

InputFile::InputFile(const std::string &path)
{
    std::ifstream ifs;
    std::vector<std::string> fileContent;
    std::string filename = std::filesystem::path(path).filename().c_str();
    std::smatch match;
    if (!std::regex_search(filename, match, std::regex("([A-Za-z0-9]+).input")))
        throw std::invalid_argument("Invalid file name");
    _name = match[1].str();
    ifs.open(path, std::ifstream::in);
    for (std::string line; std::getline(ifs, line); )
        fileContent.push_back(line);
    if (fileContent.size() != 6)
        throw std::invalid_argument("Invalid file format");
    if (fileContent[0] != "Keyboard" && fileContent[0] != "Gamepad")
        throw std::invalid_argument("Invalid file format");
    _gamepad = fileContent[0] == "Keyboard" ? false : true;
    fileContent.erase(fileContent.begin());
    if (_gamepad)
        _binds = std::make_unique<GamepadBind>(fileContent);
    else
        _binds = std::make_unique<KeyboardBind>(fileContent);
}

InputFile::InputFile(bool gamepad) : _gamepad(gamepad)
{
    _name = "Default";
    if (_gamepad)
        _binds = std::make_unique<GamepadBind>();
    else
        _binds = std::make_unique<KeyboardBind>();
}

InputFile::~InputFile()
{
}

void InputFile::save()
{
    std::ofstream file;
    std::string filename = std::string("./inputs/").append(_name).append(".input");

    std::filesystem::create_directory("./inputs");
    file.open(filename, std::ios::out);
    file << (_gamepad ? "Gamepad" : "Keyboard") << std::endl;
    file << _binds->getUpString() << std::endl;
    file << _binds->getDownString() << std::endl;
    file << _binds->getLeftString() << std::endl;
    file << _binds->getRightString() << std::endl;
    file << _binds->getPlaceString();
    file.close();
}

void InputFile::setName(const std::string &name)
{
    _name = name;
}
