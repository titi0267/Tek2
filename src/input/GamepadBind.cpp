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
    _up = (GamepadButton)stringToKey(file[0]);
    _down = (GamepadButton)stringToKey(file[1]);
    _left = (GamepadButton)stringToKey(file[2]);
    _right = (GamepadButton)stringToKey(file[3]);
    _place = (GamepadButton)stringToKey(file[4]);
    if (_up == _down || _up == _left || _up == _right || _up == _place)
        throw std::invalid_argument("Two binds shouldn't be the same");
    if (_down == _left || _down == _right || _down == _place)
        throw std::invalid_argument("Two binds shouldn't be the same");
    if (_left == _right || _left == _place)
        throw std::invalid_argument("Two binds shouldn't be the same");
    if (_right == _place)
        throw std::invalid_argument("Two binds shouldn't be the same");
}

GamepadBind::GamepadBind()
{
    _up;
    _down;
    _left;
    _right;
    _place;
}

GamepadBind::~GamepadBind()
{
}

std::string GamepadBind::getUpString()
{
    return (keyToString(_up));
}

std::string GamepadBind::getDownString()
{
    return (keyToString(_down));
}

std::string GamepadBind::getLeftString()
{
    return (keyToString(_left));
}

std::string GamepadBind::getRightString()
{
    return (keyToString(_right));
}

std::string GamepadBind::getPlaceString()
{
    return (keyToString(_place));
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