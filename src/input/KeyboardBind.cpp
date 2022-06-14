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
    _up = (KeyboardKey)stringToKey(file[0]);
    _down = (KeyboardKey)stringToKey(file[1]);
    _left = (KeyboardKey)stringToKey(file[2]);
    _right = (KeyboardKey)stringToKey(file[3]);
    _place = (KeyboardKey)stringToKey(file[4]);
    if (_up == _down || _up == _left || _up == _right || _up == _place)
        throw std::invalid_argument("Two binds shouldn't be the same");
    if (_down == _left || _down == _right || _down == _place)
        throw std::invalid_argument("Two binds shouldn't be the same");
    if (_left == _right || _left == _place)
        throw std::invalid_argument("Two binds shouldn't be the same");
    if (_right == _place)
        throw std::invalid_argument("Two binds shouldn't be the same");
}

KeyboardBind::KeyboardBind()
{
    _up = KEY_Z;
    _down = KEY_Q;
    _left = KEY_S;
    _right = KEY_D;
    _place = KEY_SPACE;
}

KeyboardBind::~KeyboardBind()
{
}

std::string KeyboardBind::getUpString()
{
    std::cout << _up << std::endl;
    return (keyToString(_up));
}

std::string KeyboardBind::getDownString()
{
    std::cout << _down << std::endl;
    return (keyToString(_down));
}

std::string KeyboardBind::getLeftString()
{
    std::cout << _left << std::endl;
    return (keyToString(_left));
}

std::string KeyboardBind::getRightString()
{
    std::cout << _right << std::endl;
    return (keyToString(_right));
}

std::string KeyboardBind::getPlaceString()
{
    std::cout << _place << std::endl;
    return (keyToString(_place));
}

int KeyboardBind::stringToKey(const std::string &str)
{
    std::smatch match;

    if (!std::regex_search(str, match, std::regex("((ARROW)_(UP|DOWN|LEFT|RIGHT))|((LETTER)_([A-Z]))|((NUMBER)_([0-9]))|(SPACE)")))
        throw std::invalid_argument("Invalid file format");
    if (match[10].str() == "SPACE")
        return (KeyboardKey::KEY_SPACE);
    if (match[5].str() == "LETTER")
        return ((KeyboardKey)match[6].str()[0]);
    if (match[8].str() == "NUMBER")
        return ((KeyboardKey)(272 + match[9].str()[0]));
    if (match[3].str() == "RIGHT")
        return (KeyboardKey::KEY_RIGHT);
    if (match[3].str() == "DOWN")
        return (KeyboardKey::KEY_DOWN);
    if (match[3].str() == "UP")
        return (KeyboardKey::KEY_UP);
    return (KeyboardKey::KEY_LEFT);
}

std::string KeyboardBind::keyToString(int keyInt)
{
    KeyboardKey key = (KeyboardKey)keyInt;

    if (key == KEY_SPACE)
        return ("SPACE");
    if (key == KEY_RIGHT)
        return ("ARROW_RIGHT");
    if (key == KEY_LEFT)
        return ("ARROW_LEFT");
    if (key == KEY_UP)
        return ("ARROW_UP");
    if (key == KEY_DOWN)
        return ("ARROW_DOWN");
    if (key >= 320 && key <= 329) {
        char a[2] = {(char)(key - 320 + 48), 0};
        return (std::string("NUMBER_").append(a));
    }
    if (key >= 65 && key <= 90) {
        char a[2] = {(char)key, 0};
        return (std::string("LETTER_").append(a));
    }
    return ("");
}


