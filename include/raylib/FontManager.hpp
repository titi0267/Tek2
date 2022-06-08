/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** FontManager
*/

#pragma once

#include <unordered_map>
#include "Font.hpp"

namespace raylib {
    class FontManager {
        std::unordered_map<std::string, Font> _fonts;

        public:
        Font &loadFont(const std::string &path)
        {
            if (_fonts.find(path) == _fonts.end())
                _fonts.insert({path, Font(path)});
            return _fonts.at(path);
        }
    };
}
