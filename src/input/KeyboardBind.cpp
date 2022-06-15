/*
** EPITECH PROJECT, 2022
** input
** File description:
** KeyboardBind
*/

#include "KeyboardBind.hpp"
#include <regex>
#include <iostream>

KeyboardBind::KeyboardBind(const std::vector<std::string> &file)
{
    for (int i = 0; i < 5; i++)
        _keys[i] = (KeyboardKey)stringToKey(file[i]);
    for (int i = 0; i < 5; i++)
        for (int ii = i + 1; ii < 5; ii++)
            if (_keys[i] == _keys[ii])
                throw std::invalid_argument("Two binds shouldn't be the same");
}

KeyboardBind::KeyboardBind()
{
    _keys = {
        KEY_Z, KEY_S, KEY_Q, KEY_D, KEY_SPACE
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
    if (it != keyToStringMap.end())
        _keys[bind] = (KeyboardKey)keyInt;
    throw std::invalid_argument("Key does not exist");
}
