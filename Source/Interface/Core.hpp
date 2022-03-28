#pragma once

#include "../../arcade-interface-master/ICore.hpp"
#include "DisplayModule.hpp"
#include "../Error/Error.hpp"

class Core : public ICore
{
    public:
        Core();
        ~Core();
        void setPixelsPerCell(std::uint32_t pixelsPerCell);
        void setFramerate(unsigned framerate);
        using Vector2u = IDisplayModule::Vector2u;
        using Color = IDisplayModule::Color;
        class Texture;
        ICore::Texture *loadTexture(const std::string &filename, char character, ICore::Color characterColor, ICore::Color backgroundColor, std::size_t width, std::size_t height);
        void openWindow(Core::Vector2u pixelsWantedWindowSize);
        using Button = DisplayModule::Button;
        bool isButtonPressed(Core::Button button);
        using MouseButtonReleaseEvent = DisplayModule::MouseButtonReleaseEvent;
        ICore::MouseButtonReleaseEvent getMouseButtonReleaseEvent();
        void startTextInput();
        std::string getTextInput();
        void endTextInput();
        struct Sprite {
            Core::Vector2u pixelPosition;
            Core::Texture *texture;
        };
        void clearScreen(Core::Color color);
        void renderSprite(Core::Sprite sprite);
        void addNewScore(std::uint32_t score);

    protected:
        Error _setError;
};
