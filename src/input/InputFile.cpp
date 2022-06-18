/*
** EPITECH PROJECT, 2022
** input
** File description:
** InputFile
*/

#include "input/InputFile.hpp"
#include "input/KeyboardBind.hpp"
#include "input/GamepadBind.hpp"
#include <fstream>
#include <iostream>
#include <regex>
#include <filesystem>

InputFile::InputFile(const std::string &path)
{
    std::ifstream ifs;
    std::vector<std::string> fileContent;
    std::string filename = std::filesystem::path(path).filename().u8string();
    std::smatch match;
    if (!std::regex_search(filename, match, std::regex("([A-Za-z0-9]+).input")))
        throw std::invalid_argument("Invalid file name");
    _name = match[1].str();
    ifs.open(path, std::ifstream::in);
    if (!ifs.good())
        throw std::invalid_argument("Invalid file");
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
    if (!file.good())
        throw std::invalid_argument("Invalid file");
    file << (_gamepad ? "Gamepad" : "Keyboard") << std::endl;
    for (int i = 0; i < 5; i++)
        file << _binds->getKeyString((IBind::Binding) i) << std::endl;
    file.close();
}

void InputFile::setName(const std::string &name)
{
    _name = name;
}

void InputFile::setKey(IBind::Binding bind, int keyInt)
{
    std::cout << bind << " " << keyInt << std::endl;
    std::cout << _gamepad << std::endl;
    _binds->setKey(bind, keyInt);
}

int InputFile::getKey(IBind::Binding bind)
{
    return (_binds->getKey(bind));
}

std::string InputFile::getKeyText(IBind::Binding bind)
{
    return (_binds->getKeyText(bind));
}

bool InputFile::getGamepad()
{
    return (_gamepad);
}