/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Text3D
*/

#include "ecs/components/Text3D.hpp"
#include "ecs/components/CameraFollow.hpp"

#include "raylib/Camera.hpp"
#include "raylib/Matrix.hpp"
#include "raylib/GL.hpp"
#include "raylib/Vectors.hpp"
#include "raylib/FontManager.hpp"

void ecs::Draw3DTextSystem::drawText3D(const std::string &str, raylib::Font &font, float fontSize, float fontSpacing, Color color)
{
    int bytesProcessed = 0;
    float offset = 0;
    float scale = fontSize / ((float) font.getBaseSize());

    for (int i = 0; i < str.length();) {
        int codepoint = font.getCodepoint(&str.c_str()[i], &bytesProcessed);
        int glyphIndex = font.getGlyphIndex(codepoint);
        GlyphInfo &glyph = font.getGlyph(glyphIndex);

        if (codepoint != ' ' && codepoint != '\t' && codepoint != '\n')
            drawTextCodepoint3D(codepoint, font, offset, fontSize, color);

        if (glyph.advanceX == 0)
            offset += (fontSpacing + font.getRect(glyphIndex).width) / (float) font.getBaseSize() * scale;
        else
            offset += (fontSpacing + glyph.advanceX) / (float) font.getBaseSize() * scale;

        i += bytesProcessed;
    }
}

void ecs::Draw3DTextSystem::drawTextCodepoint3D(int codepoint, raylib::Font &font, float offset, float fontSize, Color color)
{
    int glyphIndex = font.getGlyphIndex(codepoint);
    GlyphInfo &glyph = font.getGlyph(glyphIndex);
    Rectangle rect = font.getRect(glyphIndex);

    float scale = fontSize / ((float) font.getBaseSize());
    offset += (glyph.offsetX - font.getPadding()) / (float) font.getBaseSize() * scale;

    Rectangle srcRec = {rect.x - font.getPadding(), rect.y - font.getPadding(),
    rect.width + 2 * font.getPadding(), rect.height + 2 * font.getPadding()};

    float width = rect.width / (float) font.getBaseSize() * scale;
    float height = rect.height / (float) font.getBaseSize() * scale;
    raylib::Texture texture = font.getTexture();

    float tx = srcRec.x / (float) texture.getWidth();
    float ty = (srcRec.y + srcRec.height) / (float) texture.getHeight();
    float tw = (srcRec.x + srcRec.width) / (float) texture.getWidth();
    float th = srcRec.y / (float) texture.getHeight();

    raylib::rlCheckRenderBatchLimit(8);
    raylib::rlSetTexture(texture.getTexture().id);

    raylib::RlMatrixPush push;
    raylib::rlBegin(RL_QUADS);

    raylib::rlColor4ub({color.r, color.g, color.b, color.a});

    raylib::rlNormal3f({0.0f, 0.0f, 1.0f});

    raylib::rlTexCoord2f({tx, ty});
    raylib::rlVertex3f({offset, 0, 0});

    raylib::rlTexCoord2f({tx, th});
    raylib::rlVertex3f({offset, height, 0});

    raylib::rlTexCoord2f({tw, th});
    raylib::rlVertex3f({offset + width, height, 0});

    raylib::rlTexCoord2f({tw, ty});
    raylib::rlVertex3f({offset + width, 0, 0});

    raylib::rlNormal3f({0.0f, 0.0f, -1.0f});

    raylib::rlTexCoord2f({tx, ty});
    raylib::rlVertex3f({offset, 0, 0});

    raylib::rlTexCoord2f({tw, ty});
    raylib::rlVertex3f({offset + width, 0, 0});

    raylib::rlTexCoord2f({tw, th});
    raylib::rlVertex3f({offset + width, height, 0});

    raylib::rlTexCoord2f({tx, th});
    raylib::rlVertex3f({offset, height, 0});

    raylib::rlEnd();

    raylib::rlSetTexture(0);
}

Vector2 ecs::Draw3DTextSystem::measure3DText(const std::string &str, raylib::Font &font, float fontSize, float fontSpacing)
{
    float scale = fontSize / ((float) font.getBaseSize());
    int bytesProcessed = 0;
    float width = 0;
    float height = 0;
    float lastOffset = 0;

    for (int i = 0; i < str.length();) {
        int codepoint = font.getCodepoint(&str.c_str()[i], &bytesProcessed);
        int glyphIndex = font.getGlyphIndex(codepoint);
        GlyphInfo &glyph = font.getGlyph(glyphIndex);

        if (codepoint != ' ' && codepoint != '\t' && codepoint != '\n')
            lastOffset = (glyph.offsetX - font.getPadding()) / (float) font.getBaseSize() * scale;

        if (glyph.advanceX == 0)
            width += (fontSpacing + font.getRect(glyphIndex).width) / (float) font.getBaseSize() * scale;
        else
            width += (fontSpacing + glyph.advanceX) / (float) font.getBaseSize() * scale;

        height = font.getRect(glyphIndex).height / (float) font.getBaseSize() * scale;

        i += bytesProcessed;
    }

    return Vector2 {width, height};
}

void ecs::Draw3DTextSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Transform, Text3D, FontRef>();
}

void ecs::Draw3DTextSystem::update(ecs::World &world)
{
    raylib::Camera &cam = world.getRessource<raylib::Camera>();
    raylib::Matrix invViewMat = cam.getViewMatrix().inverse();
    raylib::FontManager &fontMan = world.getRessource<raylib::FontManager>();

    cam.begin3DMode();
    for (ecs::Entity entity : _entities) {
        Transform &transform = world.getComponent<Transform>(entity);
        Text3D &text = world.getComponent<Text3D>(entity);
        FontRef &fontRef = world.getComponent<FontRef>(entity);
        raylib::Font &font = fontMan.getFont(fontRef.fontId);

        Vector2 size = measure3DText(text.text, font, text.fontSize, text.fontSpacing);
        raylib::Matrix transformMat = raylib::Matrix::fromScale(transform.scale) * raylib::Matrix::fromQuaternion(transform.rotation);

        Vector3 trueOffset = text.offset * transformMat + Vector3 {-size.x / 2, -size.y / 2, 0} * transformMat;
        raylib::Matrix mat = raylib::Matrix::fromTransform(transform) * raylib::Matrix::fromTranslate(trueOffset);

        if (world.hasComponent<CameraFollow>(entity))
            mat = mat * invViewMat;

        raylib::RlMatrixPush push;
        raylib::rlMultMatrix(mat);

        drawText3D(text.text, font, text.fontSize, text.fontSpacing, text.color);
    }
    cam.end3DMode();
}
