/*
** EPITECH PROJECT, 2022
** input
** File description:
** KeyboardBind
*/

#pragma once

#include "IBind.hpp"
#include "raylib/headers/raylib.h"
#include <vector>
#include <string>
#include <unordered_map>

class KeyboardBind : public IBind {
    public:
        KeyboardBind(const std::vector<std::string> &file);
        KeyboardBind();
        ~KeyboardBind();
        std::string getKeyText(Binding bind);
        std::string getKeyString(Binding bind);
        int getKey(Binding bind);
        void setKey(Binding bind, int keyInt);
        int stringToKey(const std::string &str);
        std::string keyToString(int keyInt);
        std::string keyToGameTxt(int keyInt);

    protected:
        std::vector<KeyboardKey> _keys;
    private:
};

extern const std::unordered_map<KeyboardKey, std::string> keyToStringMap;
extern const std::unordered_map<KeyboardKey, std::string> keyToGameText;