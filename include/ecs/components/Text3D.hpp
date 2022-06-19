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
        char fontId[255];

        FontRef(const std::string &id = "") { id.copy(fontId, 255); fontId[id.size()] = 0; };
    };

    struct Text3D {
        char text[255];
        int textSize;
        Color color;
        Vector3 offset;
        float fontSize;
        float fontSpacing;

        Text3D(const std::string &text = "", Color color = BLACK, Vector3 offset = {0}, float fontSize = 8, float fontSpacing = 0.5)
            : color(color), offset(offset), fontSize(fontSize), fontSpacing(fontSpacing)
        {
            this->text[(textSize = text.copy(this->text, 255))] = 0;
        };

        void setText(const std::string &text)
        {
            this->text[(textSize = text.copy(this->text, 255))] = 0;
        }

        std::string getText()
        {
            return std::string(text, textSize);
        }

        std::string_view getTextView()
        {
            return std::string_view(text, textSize);
        }
    };

    class Draw3DTextSystem : public ecs::ASystem {
        void drawText3D(const std::string &str, raylib::Font &font, float fontSize, float fontSpacing, Color color);
        void drawTextCodepoint3D(int codepoint, raylib::Font &font, float offset, float fontSize, Color color);
        Vector2 measure3DText(const std::string &str, raylib::Font &font, float fontSize, float fontSpacing);

        public:
        Draw3DTextSystem() { _stage = ecs::Stages::DRAW_WORLD; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
   };
}