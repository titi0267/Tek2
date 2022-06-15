/*
** EPITECH PROJECT, 2022
** input
** File description:
** GamepadBind
*/

#include "GamepadBind.hpp"
#include <stdexcept>

GamepadBind::GamepadBind(const std::vector<std::string> &file)
{
    for (int i = 0; i < 5; i++)
        _keys[i] = (GamepadButton)stringToKey(file[i]);
    for (int i = 0; i < 5; i++)
        for (int ii = i + 1; ii < 5; ii++)
            if (_keys[i] == _keys[ii])
                throw std::invalid_argument("Two binds shouldn't be the same");
}

GamepadBind::GamepadBind()
{
    _keys = {
        GAMEPAD_BUTTON_LEFT_FACE_UP,
        GAMEPAD_BUTTON_LEFT_FACE_DOWN,
        GAMEPAD_BUTTON_LEFT_FACE_RIGHT,
        GAMEPAD_BUTTON_LEFT_FACE_LEFT,
        GAMEPAD_BUTTON_RIGHT_FACE_RIGHT,
    };
}

GamepadBind::~GamepadBind()
{
}

std::string GamepadBind::getKeyString(Binding bind)
{
    return (keyToString(_keys[(int)bind]));
}

std::string GamepadBind::getKeyText(Binding bind)
{
    return (keyToGameTxt(_keys[(int)bind]));
}

int GamepadBind::getKey(Binding bind)
{
    return (_keys[bind]);
}

int GamepadBind::stringToKey(const std::string &str)
{
    for (auto it = buttonToString.begin(); it != buttonToString.end(); it++) {
        if (it->second == str)
            return (it->first);
    }
    throw std::invalid_argument("Key does not exist");
}

std::string GamepadBind::keyToString(int keyInt)
{
    auto it = buttonToString.find((GamepadButton)keyInt);
    if (it != buttonToString.end())
        return (it->second);
    throw std::invalid_argument("Key does not exist");
}

std::string GamepadBind::keyToGameTxt(int keyInt)
{
    auto it = buttonToGameText.find((GamepadButton)keyInt);
    if (it != buttonToGameText.end())
        return (it->second);
    throw std::invalid_argument("Key does not exist");
}

void GamepadBind::setKey(Binding bind, int keyInt)
{
    auto it = buttonToString.find((GamepadButton)keyInt);
    if (it != buttonToString.end())
        _keys[bind] = (GamepadButton)keyInt;
    throw std::invalid_argument("Key does not exist");
}