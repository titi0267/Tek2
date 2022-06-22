/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Font
*/

#pragma once

#include <string>
#include "headers/raylib.h"
#include "Texture.hpp"

namespace raylib {
    using RaylibFont = ::Font;

    class Font {
        bool _created;
        RaylibFont _font;

        public:
        Font(const std::string &str) : _created(true), _font(LoadFont(str.c_str())) {};
        Font(const RaylibFont &font) : _created(false), _font(font) {};
        ~Font() { if (_created) UnloadFont(_font); };
        Font(Font &font) = delete;
        Font(Font &&font) : _created(font._created), _font(font._font) { font._created = false, font._font = { 0 }; };

        int getCodepoint(const char *str, int *bytesProcessed)
        {
            return GetCodepoint(str, bytesProcessed);
        }

        int getGlyphIndex(int codepoint)
        {
            return GetGlyphIndex(_font, codepoint);
        }

        GlyphInfo &getGlyph(int index)
        {
            return _font.glyphs[index];
        }

        Rectangle &getRect(int index)
        {
            return _font.recs[index];
        }

        int getPadding()
        {
            return _font.glyphPadding;
        }

        int getBaseSize()
        {
            return _font.baseSize;
        }

        Texture getTexture()
        {
            return Texture(_font.texture);
        }
    };
}
