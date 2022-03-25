#pragma once

#include "../../arcade-interface-master/ICore.hpp"

class Core : public ICore
{
    public:
        ~Core() = default;
        void setPixelsPerCell(std::uint32_t pixelsPerCell);
        void setFramerate(unsigned framerate);
        using Vector2u = IDisplayModule::Vector2u;
        using Color = IDisplayModule::Color;
        class Texture;
        ICore::Texture *loadTexture(const std::string &filename, char character, ICore::Color characterColor, ICore::Color backgroundColor, std::size_t width, std::size_t height);
        void openWindow(ICore::Vector2u pixelsWantedWindowSize);
        using Button = IDisplayModule::Button;
        bool isButtonPressed(ICore::Button button);
        using MouseButtonReleaseEvent = IDisplayModule::MouseButtonReleaseEvent;
        ICore::MouseButtonReleaseEvent getMouseButtonReleaseEvent();
        void startTextInput();
        std::string getTextInput();
        void endTextInput();
        struct Sprite {
            ICore::Vector2u pixelPosition;
            ICore::Texture *texture;
        };
        void clearScreen(ICore::Color color);
        void renderSprite(ICore::Sprite sprite);
        void addNewScore(std::uint32_t score);
};
