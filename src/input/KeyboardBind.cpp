/*
** EPITECH PROJECT, 2022
** input
** File description:
** KeyboardBind
*/

#include "input/KeyboardBind.hpp"
#include <regex>
#include <iostream>

KeyboardBind::KeyboardBind(const std::vector<std::string> &file)
{
    for (int i = 0; i < 5; i++)
        _keys.push_back ((KeyboardKey)stringToKey(file[i]));
    for (int i = 0; i < 5; i++)
        for (int ii = i + 1; ii < 5; ii++)
            if (_keys[i] == _keys[ii])
                throw std::invalid_argument("Two binds shouldn't be the same");
}

KeyboardBind::KeyboardBind()
{
    _keys = {
        KEY_W, KEY_S, KEY_A, KEY_D, KEY_SPACE
    };
}

KeyboardBind::~KeyboardBind()
{
}

std::string KeyboardBind::getKeyString(Binding bind)
{
    return (keyToString(_keys[(int)bind]));
}

std::string KeyboardBind::getKeyText(Binding bind)
{
    return (keyToGameTxt(_keys[(int)bind]));
}

int KeyboardBind::getKey(Binding bind)
{
    return (_keys[bind]);
}

int KeyboardBind::stringToKey(const std::string &str)
{
    for (auto it = keyToStringMap.begin(); it != keyToStringMap.end(); it++) {
        if (it->second == str)
            return (it->first);
    }
    throw std::invalid_argument("Key does not exist");
}

std::string KeyboardBind::keyToString(int keyInt)
{
    auto it = keyToStringMap.find((KeyboardKey)keyInt);
    if (it != keyToStringMap.end())
        return (it->second);
    throw std::invalid_argument("Key does not exist");
}

std::string KeyboardBind::keyToGameTxt(int keyInt)
{
    auto it = keyToGameText.find((KeyboardKey)keyInt);
    if (it != keyToGameText.end())
        return (it->second);
    throw std::invalid_argument("Key does not exist");
}

void KeyboardBind::setKey(Binding bind, int keyInt)
{
    auto it = keyToStringMap.find((KeyboardKey)keyInt);
    if (it != keyToStringMap.end()) {
        int temp = (int)_keys[bind];
        _keys[bind] = (KeyboardKey)keyInt;
        for (int i = 0; i < 5; i++) {
            if (i == (int)bind)
                continue;
            if (_keys[i] == keyInt)
                _keys[i] = (KeyboardKey)temp;
        }
        return;
    }
    throw std::invalid_argument("Key does not exist");
}
