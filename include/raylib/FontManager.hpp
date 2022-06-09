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
        Font &loadFont(const std::string &id, const std::string &path)
        {
            if (_fonts.find(id) != _fonts.end())
                throw std::runtime_error("Font ID already used");
            _fonts.insert({id, Font(path)});
            return _fonts.at(id);
        }

        Font &getFont(const std::string &id)
        {
            return _fonts.at(id);
        }
    };
}
