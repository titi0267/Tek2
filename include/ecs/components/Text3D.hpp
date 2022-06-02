/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Text3D
*/

#pragma once

#include <string>

#include "ecs/engine/System.hpp"
#include "ecs/engine/World.hpp"

#include "raylib/Font.hpp"

namespace ecs {
    struct FontRef {
        raylib::Font *font;

        FontRef(raylib::Font *font = nullptr) : font(font) {};
    };

    struct Text3D {
        std::string text;
        Color color;
        Vector3 offset;
        float fontSize;
        float fontSpacing;

        Text3D(const std::string &text = "", Color color = BLACK, Vector3 offset = {0}, float fontSize = 8, float fontSpacing = 0.5)
            : text(text), color(color), offset(offset), fontSize(fontSize), fontSpacing(fontSpacing) {};
    };

    class Draw3DTextSystem : public ecs::ASystem {
        void drawText3D(const std::string &str, raylib::Font &font, float fontSize, float fontSpacing, Color color);
        void drawTextCodepoint3D(int codepoint, raylib::Font &font, float offset, float fontSize, Color color);

        public:
        Draw3DTextSystem() { _stage = ecs::Stages::DRAW_WORLD; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
   };
}