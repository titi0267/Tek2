/*
** EPITECH PROJECT, 2022
** input
** File description:
** KeyboardBind
*/

#pragma once

#include "IBind.hpp"
#include "../bomberman/include/raylib/headers/raylib.h"
#include <vector>
#include <string>

class KeyboardBind : public IBind {
    public:
        KeyboardBind(const std::vector<std::string> &file);
        KeyboardBind();
        ~KeyboardBind();
        std::string getUpString();
        std::string getDownString();
        std::string getLeftString();
        std::string getRightString();
        std::string getPlaceString();
        int stringToKey(const std::string &str);
        std::string keyToString(int keyInt);

    protected:
        KeyboardKey _up;
        KeyboardKey _down;
        KeyboardKey _left;
        KeyboardKey _right;
        KeyboardKey _place;
    private:
};
